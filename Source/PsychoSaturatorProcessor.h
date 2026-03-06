#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

#include <juce_dsp/juce_dsp.h>

class PsychoSaturatorProcessor
{
public:
    PsychoSaturatorProcessor();
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    
    void setDrive(float value);
    void setOutputGain(float value);
    void setMix(float value);
    
private:
    // ELITE DSP: Anti-Derivative Antialiasing (ADAA)
    float adaaProcess(float x, int channel);
    float saturationFunction(float x);
    float antiderivativeFunction(float x);
    
    float drive = 1.0f;
    float outputGain = 1.0f;
    float mix = 1.0f;

    // ADAA State
    float xPrev[2] = { 0.0f, 0.0f };
    
    // RMS Auto-Gain Tracker
    float inputRMS = 0.0f;
    float outputRMS = 0.0f;
    float gainCorrection = 1.0f;

    std::unique_ptr<juce::dsp::Oversampling<float>> oversampler;
    float lastSample[2] = { 0.0f, 0.0f };
    float lastInput[2] = { 0.0f, 0.0f };
    float lastOutput[2] = { 0.0f, 0.0f };
};
