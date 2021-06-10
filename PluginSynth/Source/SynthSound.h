/*
  ==============================================================================

    SynthSound.h
    Created: 8 Jun 2021 6:54:31pm
    Author:  Tyler Wade

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }

};