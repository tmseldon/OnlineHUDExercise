# Online HUD Exercise

[Unreal 5.3] MVVM implementation for UI

This is an exercise to implement everything that we have learnt about **Unreal, UMG, and MVVM pattern**. The goal is to create a UI screen where the player could look a online and offline list of players.
The main requirements for this exercise are:

- Implement **two scrollable lists** whether using Unreal's UI elements or create your own ones. If you create your own, you must use **Object Pooling** in order to be efficient with the resources
- **Simulate** the connection and disconnection of players
- Trigger a _toast message_ if a player has connected and a _tooltip message_ if the player clicks/hover another player on the list
- Use not only mouse, but also keyboard and gamepad for the navigation
- Apply animations and effects
- and other small requirements

![](https://github.com/tmseldon/OnlineHUDExercise/assets/81703600/d5c016f6-7d64-4b1b-b211-2e6fcfe8341c)

## Design and technical challenges

- **General Architecture**: The main components in this exercise are the _GameModeExtended_ and the _HUDManager_. The GameModeExtended is responsible for simulate the connection and disconnection of players. We have a initial mock up data that we use to hydrate a "player data model". This model will retain the status during the simulation for the player on the list. The HUDManager is responsible to show the canvas that contains all the UI Widgets on this exercise, and also to serve as bridge between the data simulated from the GameModeExtended to the different widgets. For the latter, all the View Models at initialization will subscribe to the delegate that HUDManager triggers when there is any change on the player data model.
- **View model initialization**: For some reason, I had some difficulties trying to initialize manually all the View Models for each Widget. On an initial proof of concept, I didn't have too much trouble, but once I started to gather all the widgets, some pointers got messed up. Because of this reason, I opted for the automatically initialization on each Widget, and at initialization I got the pointer of that View Model through Blueprints (very relevant for the scrollable list)
- **Own Scrollable Lists**: Due the previous point and also to keep some control over each cell/position on the scrollable list, I decided to build my own scrollable list. The list is composed by three main elements: title button (that collapse/extend the list), slider and, the player cards (each cell/slot of the list). In order to not create and destroy player cards every time that we scroll or change the data, at start we create a fixed number of Player Cards that are visible on each "page" of the list. In that way, we don't need to destroy the Player Cards; in fact, we only change the data on them (when the player scroll through the slider or due connection/disconnection) making the illusion that the list is "moving". This element was the most complex on this exercise, because I nested some View Models: _ListContainerViewModel --controls--> list of  PlayerCardViewModel --call--> TooltipViewModel_
- **Other UI widgets**: The **tooltip widget** is just one element on the UI Canvas. Instead of creating one tooltip for each PlayerCard, each PLayerCard detects when the focus is on it, and calls the TooltipViewModel. One of the binding properties is related to the PlayerCard's localization that made the call. In that way, the tooltip can be re-locate when we need. The **toast message widget** is the simplest widget on the exercise, it just activates by listening the HUDManager's delegate. It activates only when the player has changed to online.
- **New Input System**: the implementation for the navigation using mouse, keyboard and gamepad was simple and direct by using the new Input System. Since I use the third view template for this exercise, the Player Controller has already some implementation for the movement. Thus, the work was to create a new Action to trigger the HUD and some tweaks for the navigation.
