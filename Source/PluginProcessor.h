/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

typedef enum {
    PRE_GAIN,
    THRESHOLD,
    POST_GAIN
} rotaryType;

inline float logisticFunction(float input, float threshold) {
    return threshold * (2 * (1 / (1 + exp(-input/threshold))) - 1);
}

inline float sigmoidFunction(float input, float threshold) {
    return threshold * (input / (1 + fabs(input/threshold)));
}

inline float arctanFunction(float input, float threshold) {
    return threshold * (2 / M_PI) * atan( (M_PI / 2) * input / threshold);
}

//==============================================================================
/**
*/
class DistortAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    DistortAudioProcessor();
    ~DistortAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float getParamValue(rotaryType);
    void setParamValue(float val, rotaryType idx);
    
private:
    std::vector<float> params = {1.0, 1.0, 0.0, 1.0};
    
    juce::dsp::BallisticsFilter<float> envelopeFollower;
    std::unique_ptr<juce::dsp::Oversampling<float>> oversamplingFilter;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortAudioProcessor)
};
