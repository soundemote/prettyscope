#include "JuceHeader.h"

// this function creates the actual plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	auto * plugin = new AudioPluginWithMidiIn(51);

	auto * module = new PrettyScopeModule(&plugin->plugInLock, &plugin->metaParaManager);

	module->setSaveAndRecallMetaParameters(true); // is this needed? - maybe it should be done in setAudioModuleToWrap

	plugin->setAudioModuleToWrap(module);
	plugin->setPluginName(module->getModuleName());

	return plugin;
}
