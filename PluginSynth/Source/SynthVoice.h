/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Jun 2021 6:54:20pm
    Author:  Tyler Wade

  ==============================================================================
*/

#pragma once
#include "SynthSound.h"
class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

    void reset();
    void SynthVoice::updateModParams(const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth, const float lfoFreq, const float lfoDepth);
private:

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;
    float filterAdsrOutput{ 0.0f };

    juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x); } };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};