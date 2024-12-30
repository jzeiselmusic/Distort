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
class DistortAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistortAudioProcessorEditor (DistortAudioProcessor&);
    ~DistortAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    const int NUM_SLIDERS = 3;
    
    std::vector<CartoonRotarySlider*> sliders;
    DistortAudioProcessor& audioProcessor;
    CartoonLookAndFeel rotarySliderLookAndFeel;
    
    void createAllSliders(void);
    void allocateAllSliders(void);
    void deallocateAllSliders(void);
    void setBoundsAllSliders(void);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortAudioProcessorEditor)
};
