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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DistortAudioProcessor& audioProcessor;
    
    CartoonRotarySlider* rotarySlider;
    CartoonLookAndFeel rotarySliderLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortAudioProcessorEditor)
};
