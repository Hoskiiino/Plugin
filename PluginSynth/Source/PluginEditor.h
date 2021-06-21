/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PluginSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PluginSynthAudioProcessorEditor (PluginSynthAudioProcessor&);
    ~PluginSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void PluginSynthAudioProcessorEditor::setSliderParams(juce::Slider& slider);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PluginSynthAudioProcessor& audioProcessor;

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::ComboBox oscSelector;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginSynthAudioProcessorEditor)
};
