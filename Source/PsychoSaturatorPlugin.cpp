#include "PsychoSaturatorPlugin.h"
#include <cmath>
#include <algorithm>

struct Preset {
    const char* name;
    float drive;
    float mix;
    float output;
    float tone;
};

static Preset presets[] = {
    { "Warm", 0.3f, 1.0f, -3.0f, 0.0f },
    { "Hot", 0.7f, 1.0f, -6.0f, 2.0f },
    { "Clean", 0.1f, 0.8f, 0.0f, -2.0f },
    { "Crushed", 0.95f, 0.7f, -12.0f, 4.0f }
};

PsychoSaturatorPlugin::PsychoSaturatorPlugin()
{
}

PsychoSaturatorPlugin::~PsychoSaturatorPlugin()
{
}

void PsychoSaturatorPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void PsychoSaturatorPlugin::releaseResources()
{
}

bool PsychoSaturatorPlugin::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    if (layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;
    return true;
}

float PsychoSaturatorPlugin::getParameter(int index) const
{
    switch (index) {
        case Drive: return driveParam;
        case Mix: return mixParam;
        case Output: return outputParam;
        case Tone: return toneParam;
        default: return 0.0f;
    }
}

void PsychoSaturatorPlugin::setParameter(int index, float newValue)
{
    switch (index) {
        case Drive: driveParam = newValue; break;
        case Mix: mixParam = newValue; break;
        case Output: outputParam = newValue; break;
        case Tone: toneParam = newValue; break;
    }
}

void PsychoSaturatorPlugin::applyPreset(int presetIndex)
{
    if (presetIndex >= 0 && presetIndex < 4) {
        driveParam = presets[presetIndex].drive;
        mixParam = presets[presetIndex].mix;
        outputParam = presets[presetIndex].output;
        toneParam = presets[presetIndex].tone;
        currentProgram = presetIndex;
    }
}

void PsychoSaturatorPlugin::setCurrentProgram(int index)
{
    applyPreset(index);
}

const juce::String PsychoSaturatorPlugin::getProgramName(int index)
{
    if (index >= 0 && index < 4) {
        return presets[index].name;
    }
    return {};
}

void PsychoSaturatorPlugin::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    
    // 1. Sync parameters with our high-end engine
    // Mapping 0.0-1.0 to professional drive range (1.0x to 8.0x)
    saturator.setDrive(1.0f + driveParam * 7.0f); 
    saturator.setMix(mixParam);
    saturator.setOutputGain(std::pow(10.0f, outputParam / 20.0f));
    
    // 2. RUN THE ENGINE
    saturator.process(buffer);
    
    // Clear remaining channels
    for (auto i = buffer.getNumChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* PsychoSaturatorPlugin::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

void PsychoSaturatorPlugin::getStateInformation (juce::MemoryBlock& destData)
{
    destData.append(&driveParam, sizeof(float));
    destData.append(&mixParam, sizeof(float));
    destData.append(&outputParam, sizeof(float));
    destData.append(&toneParam, sizeof(float));
    destData.append(&currentProgram, sizeof(int));
}

void PsychoSaturatorPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    const float* params = static_cast<const float*>(data);
    if (sizeInBytes >= sizeof(float) * 5) {
        driveParam = params[0];
        mixParam = params[1];
        outputParam = params[2];
        toneParam = params[3];
        currentProgram = ((const int*)(&params[4]))[0];
    }
}
