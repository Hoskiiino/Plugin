/*
  ==============================================================================

    SynthVoice.cpp
    Created: 8 Jun 2021 6:54:20pm
    Author:  Tyler Wade

  ==============================================================================
*/
#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
   adsr.noteOn();
    
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();


    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    reset();

    adsr.setSampleRate(sampleRate);


    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);
    gain.prepare(spec);

    gain.prepare(spec);
    gain.setGainLinear(0.07f);

    adsr.setParameters(adsrParams);

    isPrepared = true;
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

   /* filterAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());*/
    /*filterAdsrOutput = filterAdsr.getNextSample();*/

    synthBuffer.clear();

   /* for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc1[ch].processNextSample(buffer[s]) + osc2[ch].processNextSample(buffer[s]);
        }
    }*/

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

   /* for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            lfoOutput[ch] = lfo[ch].processSample (synthBuffer.getSample (ch, s));
            buffer[s] = filter[ch].processNextSample(ch, synthBuffer.getSample(ch, s));
        }
    }*/

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::reset()
{
    gain.reset();
    adsr.reset();
    /*filterAdsr.reset();*/
}

void SynthVoice::updateModParams(const int filterType, const float filterCutoff, const float filterResonance, const float adsrDepth, const float lfoFreq, const float lfoDepth)
{
   /* auto cutoff = (adsrDepth * filterAdsrOutput) + filterCutoff;
    cutoff = std::clamp<float>(cutoff, 20.0f, 20000.0f);

    for (int ch = 0; ch < numChannelsToProcess; ++ch)
    { 
        filter[ch].setParams(filterType, cutoff, filterResonance);
    }*/

    //    auto cutoff = (adsrDepth * adsr.getNextSample()) + filterCutoff;
    //
    //    DBG (cutoff);
    //
    //    for (int ch = 0; ch < numChannelsToProcess; ++ch)
    //    {
    //        lfo[ch].setFrequency (lfoFreq);
    //        //cutoff = (lfoDepth * lfoOutput[ch]) + cutoff;
    //        cutoff = std::clamp<float> (cutoff, 20.0f, 20000.0f);
    //        filter[ch].setParams (filterType, cutoff, filterResonance);
    //    }
}
