#include "PluginProcessor.h"
#include "PluginEditor.h"

WaveScopeAudioProcessor::WaveScopeAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
    , leftQueue (48000)   // храним ~1 секунду при 48k
    , rightQueue(48000)
{
}

void WaveScopeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

bool WaveScopeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Поддерживаем только моно или стерео, вход=выход
    if (layouts.getMainInputChannelSet() != layouts.getMainOutputChannelSet())
        return false;

    auto set = layouts.getMainOutputChannelSet();
    return set == juce::AudioChannelSet::mono() || set == juce::AudioChannelSet::stereo();
}

void WaveScopeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const int numSamples = buffer.getNumSamples();

    // Пробрасываем сигнал без изменений (through)
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        (void) buffer.getWritePointer (ch); // ничего не меняем

    // Кладём данные в очереди (без блокировок)
    const float* left  = buffer.getReadPointer (0);
    const float* right = buffer.getNumChannels() > 1 ? buffer.getReadPointer (1) : nullptr;

    leftQueue.push (left, numSamples);
    if (right) rightQueue.push (right, numSamples);
    else       rightQueue.push (left, numSamples); // дублируем моно в правую
}

juce::AudioProcessorEditor* WaveScopeAudioProcessor::createEditor()
{
    return new WaveScopeAudioProcessorEditor (*this);
}
