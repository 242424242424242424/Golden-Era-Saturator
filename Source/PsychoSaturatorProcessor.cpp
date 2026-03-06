#include "PsychoSaturatorProcessor.h"
#include <cmath>
#include <algorithm>

PsychoSaturatorProcessor::PsychoSaturatorProcessor()
{
    // High-quality Polyphase IIR Oversampling (4x)
    oversampler = std::make_unique<juce::dsp::Oversampling<float>>(2, 2, juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR, true);
}

void PsychoSaturatorProcessor::prepare(double sampleRate, int samplesPerBlock)
{
    oversampler->initProcessing(samplesPerBlock);
    oversampler->reset();
}

void PsychoSaturatorProcessor::setDrive(float value) { drive = value; }
void PsychoSaturatorProcessor::setOutputGain(float value) { outputGain = value; }
void PsychoSaturatorProcessor::setMix(float value) { mix = value; }

// --- ELITE ADAA (Anti-Derivative Antialiasing) ---
float PsychoSaturatorProcessor::saturationFunction(float x) {
    // Advanced Saturation: Soft Clipping with Analog Response
    return std::tanh(x);
}

float PsychoSaturatorProcessor::antiderivativeFunction(float x) {
    // Integral of tanh(x) = ln(cosh(x))
    // We use std::log(std::cosh(x)) with safety for large x
    float absX = std::abs(x);
    if (absX > 20.0f) return absX - 0.69314718056f; // Approximation for stability
    return std::log(std::cosh(x));
}

float PsychoSaturatorProcessor::adaaProcess(float x, int channel) {
    float x_n = x * drive;
    float x_prev = xPrev[channel];
    float delta = x_n - x_prev;
    
    float y;
    // DIVISION BY ZERO SAFETY: If x is constant, use standard function
    if (std::abs(delta) < 1e-6f) {
        y = saturationFunction(x_n);
    } else {
        // ADAA Formula: (F(x_n) - F(x_prev)) / (x_n - x_prev)
        y = (antiderivativeFunction(x_n) - antiderivativeFunction(x_prev)) / delta;
    }
    
    xPrev[channel] = x_n;
    
    // DC Filter (High-pass 10Hz) to keep phase alignment
    float filtered = 0.997f * (lastOutput[channel] + y - lastInput[channel]);
    lastInput[channel] = y;
    lastOutput[channel] = filtered;
    
    return filtered;
}

void PsychoSaturatorProcessor::process(juce::AudioBuffer<float>& buffer)
{
    int numChannels = buffer.getNumChannels();
    int numSamples = buffer.getNumSamples();

    // 1. RMS AUTO-GAIN TRACKING (Input)
    float inRMS = buffer.getRMSLevel(0, 0, numSamples) + 1e-9f;

    // 2. OVERSAMPLING & PROCESSING
    juce::dsp::AudioBlock<float> inputBlock(buffer);
    juce::dsp::AudioBlock<float> upsampledBlock = oversampler->processSamplesUp(inputBlock);
    
    int upNumChannels = (int)upsampledBlock.getNumChannels();
    int upNumSamples = (int)upsampledBlock.getNumSamples();
    
    for (int channel = 0; channel < upNumChannels; ++channel)
    {
        float* data = upsampledBlock.getChannelPointer(channel);
        int chIdx = std::min(channel, 1);
        
        for (int i = 0; i < upNumSamples; ++i)
        {
            float dry = data[i];
            
            // ELITE DSP: ADAA Processing
            float wet = adaaProcess(dry, chIdx);
            
            // MIXING
            data[i] = (wet * mix) + (dry * (1.0f - mix));
        }
    }
    
    oversampler->processSamplesDown(inputBlock);

    // 3. RMS AUTO-GAIN TRACKING (Output & Gain Matching)
    float outRMS = buffer.getRMSLevel(0, 0, numSamples) + 1e-9f;
    
    // Automatic Compensation so "Drive" doesn't change perceived volume
    float targetGain = (inRMS / outRMS) * outputGain;
    buffer.applyGain(targetGain);
    
    // Denormal Protection: Force zero for tiny values to save CPU
    for (int ch = 0; ch < numChannels; ++ch) {
        auto* data = buffer.getWritePointer(ch);
        for (int i = 0; i < numSamples; ++i) {
            if (std::abs(data[i]) < 1e-15f) data[i] = 0.0f;
        }
    }
}
