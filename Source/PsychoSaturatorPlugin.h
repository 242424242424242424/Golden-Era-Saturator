#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

#include "PsychoSaturatorProcessor.h"

class PsychoSaturatorPlugin : public juce::AudioProcessor
{
public:
    PsychoSaturatorPlugin();
    ~PsychoSaturatorPlugin() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "PsychoSaturator"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 4; }
    int getCurrentProgram() override { return currentProgram; }
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int, const juce::String&) override {}

    void getStateInformation (juce::MemoryBlock&) override;
    void setStateInformation (const void*, int) override;

    float getParameter(int index) const;
    void setParameter(int index, float newValue);
    
    enum ParameterIndex { Drive, Mix, Output, Tone };

private:
    int currentProgram = 0;
    
    float driveParam = 0.5f;
    float mixParam = 1.0f;
    float outputParam = -6.0f;
    float toneParam = 0.0f;
    
    // NEW: Our high-end saturation engine
    PsychoSaturatorProcessor saturator;
    
    void applyPreset(int presetIndex);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PsychoSaturatorPlugin)
};
