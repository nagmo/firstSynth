/*
  ==============================================================================

    SineWaveSynth.h
    Created: 12 Jan 2018 5:09:15pm
    Author:  Nevo Agmon

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

// describe the sound of the synth
class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound() = default;
    ~SineWaveSound() = default;
    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }
};

//====================================================================================

//describe each voice of the synth.
//DSP sound proceccing done here.
class SineWaveVoice : public SynthesiserVoice
{
public:
    SineWaveVoice() = default;
    ~SineWaveVoice() = default;
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }
    
    void startNote (int midiNoteNumber,float velocity,
                    SynthesiserSound*,int) override
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        level = velocity;
    }
    
    void stopNote (float, bool) override
    {
        level = 0;
        clearCurrentNote();
    }
    
    void renderNextBlock (AudioSampleBuffer& outputBuffer,int startSample,
                          int numberSamples) override
    {
        while (--numberSamples >= 0)
        {
            // Insert DSP here to fill up the buffer!
            const float currentSample = level;
            
            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample (i, startSample, currentSample);
            
            ++startSample;
        }
    }
    
    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}
    
    
private:
    // Maximilian objects declared here!
    double frequency;
    double level;
};
