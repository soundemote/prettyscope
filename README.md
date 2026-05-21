## `# prettyscope-old`

`OLD home of the pretty oscilloscope (not yet ready for serious use)`

⚱ instead of trying to salvage this project, let this be a gravestone ⚱

🦴 we will collect the bones for a new body
* I WILL MAKE IT FROM SCRATCH IN A NEW REPOSITORY
`* * when i have time`

### `# GOALS`

```adoc
* i want  prettyscope to be the standard for digital synths
* i want all digital synths around the world to use prettyscope to show their waveforms
* i want prettyscope to be free for humanity forever
* i want it to be developed as a library for building your own aesthetic oscilloscope
* the perfect "do it all" oscilloscope, best of all worlds
* highly customizable for whatever you want to use it for
```

```markdown

* desperately needs a small dedicated community
* official discord: https://discord.gg/hjpBC8kZ3s ← invite link
1. currently draws 1/4 screen on retina display
2. needs proper frame adhesion the prevent glitchy drawing and screen tearing
3. needs the implement realtime editing of shaders for quick swapping of visual fx
4. annoyingly draws an unneeded line across the screen for 1d mode since it's just a dumb repurposing of the x y mode
5. code cleanup and clarity
```

dependency hell, will solve as i have time:

# Required Software #

https://shop.juce.com/get-juce/download

# Dependencies #

`#### RS-MET ####`
* https://github.com/elanhickler/RS-MET 
* (use juce code from here, not a separate JUCE repository!)

`#### VST-SDK ####`
* MISSING: VST3 SDK 3.6.5

`#### SoundemoteFramework ####`
* https://gitlab.com/Hickler/soundemoteframework

`#### ElanJuceHelpers ####`
* https://gitlab.com/Hickler/elanjucehelpers

# Folder structure #
(everything is top level next to each other)
* PrettyScope/files
* RS-MET/files
* VST3 SDK/files
* ElanJuceHelpers/elan_juce_helpers/files
* SoundemoteFramework/se_framework/files


