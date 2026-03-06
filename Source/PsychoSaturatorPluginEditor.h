#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>

class PsychoSaturatorEditor : public juce::AudioProcessorEditor
{
public:
    PsychoSaturatorEditor(juce::AudioProcessor&);
    ~PsychoSaturatorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessor& processor;
    juce::Slider driveSlider, mixSlider, outputSlider, toneSlider;
    juce::Label driveLabel, mixLabel, outputLabel, toneLabel;
};
