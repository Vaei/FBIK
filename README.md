# FBIK (Full-Body IK) <img align="right" width=128, height=128 src="https://github.com/Vaei/FBIK/blob/main/Resources/Icon128.png">

> [!IMPORTANT]
> **FBIK (Full-Body IK)**
> <br>Provides an Anim Graph Node that reproduces the behaviour of Control Rig Full Body IK node
> <br>And its **FREE!**

> [!NOTE]
> The Full Body IK node in Control Rig is really good
> <br>Climbing ladders, proning on the ground, mantling all benefit from a good FBIK solution
> <br>However Control Rig can be clunky and take a lot of work to get setup, this allows you to get the same behaviour without any Control Rig

# Installation

## Pre-Compiled Binaries

> [!IMPORTANT]
> This is the easy method for new users but not the recommended method
> <br>These can be installed either to your project or the engine
> <br>These are available for Win64 only

> [!NOTE]
> Only the 2 most recent engine versions are included
> <br>Pre-Compiled binaries may be delayed, for the quickest access to latest release, use `git clone`

Download the version that corresponds to the engine version you are using.

[Download for 5.6](TODO) or 
[Download for 5.5](TODO)

Create a `Plugins` folder in your project directory, or you can create it in your Engine's `Plugins\Marketplace` folder if you would prefer to install to the engine instead. Extract the plugin from the zip file into this folder.

When you load your project, open the Plugins window ( `Edit` ➜ `Plugins` ), and enable `FBIK` then restart the editor.

## Git Clone

> [!IMPORTANT]
> This is the recommended method
> <br>The plugin needs to be added to your project, and not the engine

> [!CAUTION]
> Your project will need to be compiled, so it needs to be a code project

Create a Plugins folder in your project directory if it does not already exist.

Use `git clone https://github.com/Vaei/FBIK.git` and clone it into this `Plugins` folder.

Right click your .uproject (not the .uplugin) and `Generate Visual Studio project files`.

If you attempt to open your project it will ask "The following modules are missing or built with a different engine version".

Click "Yes".

If you get the error "ProjectName could not be compiled. Try rebuilding from source manually.", then open your project in your IDE. This typically means double-clicking the .sln if using Visual Studio. Now compile the project from your IDE. If you get a compiler error then you can find out the reason why it could not compile.

Feel free to `@vaei` on [Unreal Source Discord](https://discord.com/invite/unrealsource) in the `#ue5-general` channel for help.

# Next Stages

The "Full-Body IK" node will now be available to use in Anim Graph.

## Changelog

### 1.0.0
* Initial Release
