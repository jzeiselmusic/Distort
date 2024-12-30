/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CartoonLookAndFeel.h"

//==============================================================================
DistortAudioProcessorEditor::DistortAudioProcessorEditor (DistortAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(500, 300);
    setResizable(true, true);
    rotarySlider = new CartoonRotarySlider;
    rotarySlider->setRange(0.0, 1.0);
    rotarySlider->setValue(0.5);
    rotarySlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rotarySlider->setLookAndFeel(&rotarySliderLookAndFeel);
    rotarySlider->setBounds(getWidth()/4, getHeight()/4, getWidth()/2, getHeight()/2);

    addAndMakeVisible(*rotarySlider);
}

DistortAudioProcessorEditor::~DistortAudioProcessorEditor()
{
    delete rotarySlider;
}

//==============================================================================
void DistortAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillAll();  // Ensure no clipping is limiting the drawing region
}

void DistortAudioProcessorEditor::resized()
{
    if (rotarySlider) {
        rotarySlider->setBounds(getWidth()/4, getHeight()/4, getWidth()/2, getHeight()/2);
    }
}
