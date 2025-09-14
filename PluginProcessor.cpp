#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessor::AudioPluginAudioProcessor()
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::discreteChannels(32), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
{
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioPluginAudioProcessor::getNumPrograms()
{
    return 1;   
                
}

int AudioPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioPluginAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String AudioPluginAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused (sampleRate, samplesPerBlock);
    
    juce::dsp::ProcessSpec spec {sampleRate, (juce::uint32) samplesPerBlock, 2};
    
    for (size_t i = 0; i < convArray.size(); ++i) {
        convArray[i].prepare(spec);
    }

    for (size_t i = 0; i < convArray.size(); ++i) {
        const juce::String resourceName = "zimmt_brir_lspk" + juce::String(i + 1) + "_wav";
    
        int dataSize = 0;
        const void* data = BinaryData::getNamedResource(resourceName.toRawUTF8(), dataSize);
    
        if (data != nullptr) {
            convArray[i].loadImpulseResponse(data, static_cast<size_t>(dataSize),
                                             juce::dsp::Convolution::Stereo::yes,
                                             juce::dsp::Convolution::Trim::no, 0);
        }
    }
}

void AudioPluginAudioProcessor::releaseResources()
{
}

bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& /*layouts*/) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // supports 32-channel input to stereo output
    return true;
  #endif
}

void AudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                              juce::MidiBuffer& /*midiMessages*/)
{
    if (getTotalNumInputChannels() < 32 || currentMode != 1) {
        return;
    }

    const int numSamples = buffer.getNumSamples();

    juce::AudioBuffer<float> inputBuffer(2, numSamples);
    juce::AudioBuffer<float> outputBuffer(2, numSamples);
    outputBuffer.clear();

    for (int i = 0; i < 32; ++i) {
        juce::dsp::AudioBlock<float> inputBlock(buffer);
        auto monoIn = inputBlock.getSingleChannelBlock(static_cast<size_t>(i));

        inputBuffer.clear();
        juce::dsp::AudioBlock<float> stereoBlock(inputBuffer);

        auto context = juce::dsp::ProcessContextReplacing<float>(stereoBlock);
        stereoBlock.getSingleChannelBlock(0).copyFrom(monoIn);
        stereoBlock.getSingleChannelBlock(1).copyFrom(monoIn);

        convArray[static_cast<size_t>(i)].process(context);

        auto* outL = outputBuffer.getWritePointer(0);
        auto* outR = outputBuffer.getWritePointer(1);
        auto* inL = inputBuffer.getReadPointer(0);
        auto* inR = inputBuffer.getReadPointer(1);

        for (int s = 0; s < numSamples; ++s) {
            outL[s] += inL[s] / 32.0f;
            outR[s] += inR[s] / 32.0f;
        }
    }
    
    buffer.clear();
    buffer.copyFrom(0, 0, outputBuffer, 0, 0, numSamples);
    buffer.copyFrom(1, 0, outputBuffer, 1, 0, numSamples);

    buffer.applyGain(16.0f * volume); // Compensate BRIR gain reduction
}

//==============================================================================
bool AudioPluginAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor()
{
    return new AudioPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused (destData);
}

void AudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::ignoreUnused (data, sizeInBytes);
}

//==============================================================================
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPluginAudioProcessor();
}
