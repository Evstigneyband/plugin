#include "PluginEditor.h"
#include "PluginProcessor.h"

WaveScopeAudioProcessorEditor::WaveScopeAudioProcessorEditor (WaveScopeAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processorRef (p)
    , scope (processorRef.leftQueue, processorRef.rightQueue)
{
    setResizable (true, true);
    setSize (720, 360);
    addAndMakeVisible (scope);
}

void WaveScopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void WaveScopeAudioProcessorEditor::resized()
{
    scope.setBounds (getLocalBounds());
}
