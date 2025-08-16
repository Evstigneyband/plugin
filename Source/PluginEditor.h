#pragma once
#include <JuceHeader.h>
#include "Oscilloscope.h"

class WaveScopeAudioProcessor;

class WaveScopeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit WaveScopeAudioProcessorEditor (WaveScopeAudioProcessor&);
    ~WaveScopeAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    WaveScopeAudioProcessor& processorRef;
    OscilloscopeComponent scope;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveScopeAudioProcessorEditor)
};
