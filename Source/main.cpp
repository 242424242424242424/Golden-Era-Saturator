#include "PsychoSaturatorPlugin.h"

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PsychoSaturatorPlugin();
}
