/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CartoonRotarySlider.h"
#include "CartoonLookAndFeel.h"

//==============================================================================
/**
*/
class DistortAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Slider::Listener
{
public:
    DistortAudioProcessorEditor (DistortAudioProcessor&);
    ~DistortAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* slider) override;

private:
    const int NUM_SLIDERS = 4;
    
    std::vector<CartoonRotarySlider*> sliders;
    DistortAudioProcessor& audioProcessor;
    
    void createAllSliders(void);
    void allocateAllSliders(void);
    void deallocateAllSliders(void);
    void setBoundsAllSliders(void);
    void updateValuesAllSliders(void);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortAudioProcessorEditor)
};
