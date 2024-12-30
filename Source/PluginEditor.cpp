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
    
    allocateAllSliders();
    createAllSliders();
    setBoundsAllSliders();
}

DistortAudioProcessorEditor::~DistortAudioProcessorEditor()
{
    deallocateAllSliders();
}

//==============================================================================
void DistortAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillAll();  // Ensure no clipping is limiting the drawing region
}

void DistortAudioProcessorEditor::resized()
{
    setBoundsAllSliders();
}

void DistortAudioProcessorEditor::createAllSliders(void) {
    for (auto slider : sliders) {
        slider->setRange(0.0, 1.0);
        slider->setValue(0.5);
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider->setLookAndFeel(&rotarySliderLookAndFeel);
        addAndMakeVisible(*slider);
    }
}

void DistortAudioProcessorEditor::allocateAllSliders(void) {
    for (auto i = 0; i < NUM_SLIDERS; i++) {
        sliders.push_back(new CartoonRotarySlider);
    }
}

void DistortAudioProcessorEditor::deallocateAllSliders(void) {
    for (auto slider : sliders) {
        delete slider;
    }
}

void DistortAudioProcessorEditor::setBoundsAllSliders(void) {
    int separatorWidth = getWidth() / (NUM_SLIDERS*2 + NUM_SLIDERS + 1);
    int separatorHeight = getHeight() / 4;
    int idx = 0;
    for (auto slider : sliders) {
        if (slider) {
            slider->setBounds(
                  separatorWidth + idx * separatorWidth * 3,
                  separatorHeight,
                  separatorWidth * 2,
                  separatorHeight * 2);
        }
        idx++;
    }
}
