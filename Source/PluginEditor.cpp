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
    updateValuesAllSliders();
}

void DistortAudioProcessorEditor::createAllSliders(void) {
    auto idx = 0;
    for (auto slider : sliders) {
        if (idx == 0 || idx == 2) {
            slider->setRange(0.5, 1.5);
        }
        else {
            slider->setRange(0.0, 1.0);
        }
        slider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        slider->setLookAndFeel(&rotarySliderLookAndFeel);
        slider->addListener(this);
        addAndMakeVisible(*slider);
        idx++;
    }
    updateValuesAllSliders();
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
    auto idx = 0;
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

void DistortAudioProcessorEditor::updateValuesAllSliders(void) {
    auto idx = 0;
    for (auto slider : sliders) {
        slider->setValue(audioProcessor.getParamValue(rotaryType(idx)));
        idx++;
    }
}

void DistortAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    auto idx = 0;
    for (auto slider_ptr : sliders) {
        if (slider == slider_ptr) {
            audioProcessor.setParamValue(slider->getValue(), rotaryType(idx));
        }
        idx ++;
    }
}
