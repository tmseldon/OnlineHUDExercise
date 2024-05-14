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

- **General Architecture**: The main components in this exercise are the _GameModeExtended_ and the _HUDManager_. The GameModeExtended is responsible for simulate the connection and disconnection of players. We have a initial mock up data that we use to hydrate a "player data model". This model will retain the status during the simulation for the player on the list. The HUDManager is responsible to control all the UI Widgets on this exercise, and also to serve as bridge between the data simulated from the GameModeExtended to the different widgets. 
- **Own Scrollable Lists**: 
- **View model initialization**:
- **Other UI widgets**:
  
- **New Input System**: the implementation for the navigation using mouse, keyboard and gamepad was simple and direct by using the new Input System. Since I use the third view template for this exercise, the Player Controller has already some implementation for the movement. Thus, the work was to create a new Action to trigger the HUD and some tweaks for the navigation.
