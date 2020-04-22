# Hazel

![Hazel](/Resources/Branding/Hazel_Logo_Text_Light_Square.png?raw=true "Hazel")

Hazel is primarily an early-stage interactive application and rendering engine for Windows. Currently not much is implemented, however (almost) everything inside this repository is being created within YouTube videos, found at [thecherno.com/engine](https://thecherno.com/engine). 

## Getting Started
Visual Studio 2017 or 2019 is recommended, Hazel is officially untested on other development environments whilst we focus on a Windows build.

You can clone the repository to a local destination using git:

`git clone --recursive https://github.com/TheCherno/Hazel`

Make sure that you do a `--recursive` clone to fetch all of the submodules!

## The Plan
The plan for Hazel is two-fold: to create a powerful 3D engine, but also to serve as an education tool for teaching game engine design and architecture. Because of this the development inside this repository is rather slow, since everything has to be taught and implemented on-camera. There is a much more advanced version of the engine in a private repository called `Hazel-dev`, accessible to supporters on [Patreon](https://patreon.com/thecherno). The plan for this project is to mostly take already implemented code from the `Hazel-dev` repository and integrate it into this one, done within videos and supported by explanations.

### Main features to come:
- Fast 2D rendering (UI, particles, sprites, etc.)
- High-fidelity Physically-Based 3D rendering (this will be expanded later, 2D to come first)
- Support for Mac, Linux, Android and iOS
    - Native rendering API support (DirectX, Vulkan, Metal)
- Fully featured viewer and editor applications
- Fully scripted interaction and behavior
- Integrated 3rd party 2D and 3D physics engine
- Procedural terrain and world generation
- Artificial Intelligence
- Audio system

## This Fork
This fork of the Hazel repo adds a sample application built with the Hazel engine.
This is in the HelloBoulder subdirectory.

HelloBoulder is a clone of the popular 1980's game [Boulder-Dash](https://boulder-dash.
com).  The goal here was not to make the perfect boulder-dash clone, but rather just to demonstrate making a simple game with Hazel, in particular making use of the batched rendering of textured quads.

Many other people have made Boulder-dash clones, in particular I relied on these two for tips on the game logic:
- [Jake Gordon's remake in Javascript](https://codeincomplete.com/posts/javascript-boulderdash/)
- [Czirkos Zoltán's GDash](https://bitbucket.org/czirkoszoltan/gdash/src/master/)

### Instructions
Move Rockford around with the WASD keys (or cursor keys).  Collect the diamonds and then make your way to the exit (flashing rectangle) to progress to next level.
Do not get squashed by falling boulders, or exploded by nasties.
If you drop boulders onto butterflies, they turn into diamonds.
Press spacebar to restart if you die.

In DEBUG build, things that will kill you are highlighted in red, plus you get imgui panel to configure various things.

