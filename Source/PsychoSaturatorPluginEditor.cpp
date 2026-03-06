#include "PsychoSaturatorPlugin.h"
#include "PsychoSaturatorProcessor.h"
#include "PsychoSaturatorPluginEditor.h"

PsychoSaturatorEditor::PsychoSaturatorEditor(juce::AudioProcessor& p)
    : AudioProcessorEditor(p), processor(p)
{
    setSize(500, 400);
    
    driveSlider.setRange(0, 100);
    driveSlider.setValue(50);
    addAndMakeVisible(driveSlider);
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.attachToComponent(&driveSlider, true);
    addAndMakeVisible(driveLabel);
    
    mixSlider.setRange(0, 100);
    mixSlider.setValue(100);
    addAndMakeVisible(mixSlider);
    mixLabel.setText("Mix", juce::dontSendNotification);
    mixLabel.attachToComponent(&mixSlider, true);
    addAndMakeVisible(mixLabel);
    
    outputSlider.setRange(-20, 0);
    outputSlider.setValue(-6);
    addAndMakeVisible(outputSlider);
    outputLabel.setText("Output", juce::dontSendNotification);
    outputLabel.attachToComponent(&outputSlider, true);
    addAndMakeVisible(outputLabel);

    toneSlider.setRange(-12, 12);
    toneSlider.setValue(0);
    addAndMakeVisible(toneSlider);
    toneLabel.setText("Tone", juce::dontSendNotification);
    toneLabel.attachToComponent(&toneSlider, true);
    addAndMakeVisible(toneLabel);
}

PsychoSaturatorEditor::~PsychoSaturatorEditor() {}

void PsychoSaturatorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::limegreen);
    g.setFont(28);
    g.drawText("PSYCHO SATURATOR", 10, 15, 480, 40, juce::Justification::centred);
    
    g.setFont(14);
    g.setColour(juce::Colours::darkgreen);
    g.drawText("v1.0 - Audio Plugin", 10, 50, 480, 20, juce::Justification::centred);
}

void PsychoSaturatorEditor::resized()
{
    driveSlider.setBounds(120, 100, 320, 30);
    mixSlider.setBounds(120, 160, 320, 30);
    outputSlider.setBounds(120, 220, 320, 30);
    toneSlider.setBounds(120, 280, 320, 30);
}
