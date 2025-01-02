/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortAudioProcessor::DistortAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    envelopeFollower.prepare((juce::dsp::ProcessSpec) { 44100, 1, 2});
    envelopeFollower.setAttackTime(1);
    envelopeFollower.setReleaseTime(10);
    envelopeFollower.reset(0.0);
}

DistortAudioProcessor::~DistortAudioProcessor()
{
}

//==============================================================================
const juce::String DistortAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DistortAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistortAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistortAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DistortAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int i = 0; i < buffer.getNumSamples(); i++) {
            
            float* sample = &channelData[i];
            
            // pre-gain stage
            *sample *= params[0];
            
            // TODO: oversampling to remove aliasing
            
            // create fuzz by pushing values up by 40% of env level
            float envLevel = envelopeFollower.processSample(channel, *sample);
            *sample += 0.4 * envLevel;
            
            // normalized threshold tanh stage
            // *sample = params[1] * tanh(*sample / params[1]);
            
            // normalized threshold arctan stage
            *sample = params[1] * (2 / M_PI) * atan( (M_PI / 2) * *sample / params[1]);
            
            // normalized threshold logistic function
            // *sample = logisticFunction(*sample, params[1]);
            
            // normalized sigmoid function
            // *sample = sigmoidFunction(*sample, params[1]);
            
            
            // post-gain stage
            *sample *= params[2];
        }
    }
}

//==============================================================================
bool DistortAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistortAudioProcessor::createEditor()
{
    return new DistortAudioProcessorEditor (*this);
}

//==============================================================================
void DistortAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistortAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

float DistortAudioProcessor::getParamValue(rotaryType val) {
    return params[val];
}

void DistortAudioProcessor::setParamValue(float val, rotaryType idx) {
    params[idx] = val;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortAudioProcessor();
}
