#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    setSize(400, 200);

    bypassWindow = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(BinaryData::zimmt_bypassWindow_svg));
    decodeWindow = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(BinaryData::zimmt_decodeWindow_svg));
    
    buttonOnSVG = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(BinaryData::zimmt_buttonOn_svg));
    buttonOnHoverSVG = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(BinaryData::zimmt_buttonOn_hover_svg));

    buttonOffSVG = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(BinaryData::zimmt_buttonOff_svg));
    buttonOffHoverSVG = juce::Drawable::createFromSVG(*juce::XmlDocument::parse(BinaryData::zimmt_buttonOff_hover_svg));

    addAndMakeVisible(currentStateButton);
    currentStateButton.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentWhite);
    currentStateButton.setClickingTogglesState(true);
    updateButtonImage();

    currentStateButton.onClick = [this]()
    {
        buttonIsOn = !buttonIsOn;
        processorRef.currentMode = buttonIsOn;
        updateButtonImage();
        repaint();
    };

    addAndMakeVisible(volumeSlider);
    volumeSlider.setLookAndFeel(&customSliderLookAndFeel);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colour::fromString("ff363732"));
    volumeSlider.setRange(-70, 12, 0);

    volumeSlider.onValueChange = [this]()
    {
        processorRef.dbtoamp((float)volumeSlider.getValue());
    };
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    volumeSlider.setLookAndFeel(nullptr);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    if(bypassWindow != nullptr)
    {
        bypassWindow->setBounds(getLocalBounds());
        bypassWindow->draw(g, 1.0f);
    }

    if(buttonIsOn && decodeWindow != nullptr)
    {
        decodeWindow->setBounds(getLocalBounds());
        decodeWindow->draw(g, 1.0f);
    }
}

void AudioPluginAudioProcessorEditor::resized()
{
    currentStateButton.setBounds(84, 140, 88, 25);
    volumeSlider.setBounds(60, 95, 135, 30);
}

void AudioPluginAudioProcessorEditor::updateButtonImage()
{
    if(buttonIsOn)
    {
        currentStateButton.setImages(buttonOnSVG.get(), buttonOnHoverSVG.get(), nullptr);
    }
    else
    {
        currentStateButton.setImages(buttonOffSVG.get(), buttonOffHoverSVG.get(), nullptr);
    }

    if(bypassWindow != nullptr)
       bypassWindow->setBounds(getLocalBounds());

    if(decodeWindow != nullptr)
       decodeWindow->setBounds(getLocalBounds());

}