#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class CustomSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawLinearSlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, float, float,
                           const juce::Slider::SliderStyle, juce::Slider& slider) override
    {
        g.setColour(slider.findColour(juce::Slider::trackColourId));
        g.fillRect(x, y + height / 2 - 1, width, 2);

        g.setColour(slider.findColour(juce::Slider::thumbColourId));
        g.fillEllipse(sliderPos - 5, y + height / 2 - 5, 10, 10);
    }
};

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AudioPluginAudioProcessor& processorRef;  
    CustomSliderLookAndFeel customSliderLookAndFeel;  
        
    std::unique_ptr<juce::Drawable> bypassWindow;   
    std::unique_ptr<juce::Drawable> decodeWindow;   
    
    juce::DrawableButton currentStateButton {"State Button", juce::DrawableButton::ImageFitted };

    std::unique_ptr<juce::Drawable> buttonOnSVG;        
    std::unique_ptr<juce::Drawable> buttonOnHoverSVG;   
    std::unique_ptr<juce::Drawable> buttonOffSVG;       
    std::unique_ptr<juce::Drawable> buttonOffHoverSVG;  

    bool buttonIsOn = false;  
    void updateButtonImage(); 

    juce::Slider volumeSlider;  

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
