# Car Racing Game (Micromachines)

# Group
- Michael Chen
- Petteri Suonpää
- Hanjemma Jeong
- Kevin Kabras

# Repository organization
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Project Implementation 

## 1. Scope of Work

### Features and Functionalities

- **Basic Gameplay**: A top-down driving game where players control toy cars with simple, accessible driving physics. The camera follows the player for an immersive experience.
- **Multiple Tracks**: (If time permits) Tracks will be loaded from external files, allowing diverse game environments.
- **Game Objects**: Interactive objects (oil spills, jams, boosts) will add variety and challenge by impacting gameplay dynamics.

### Additional Gameplay Features

- **Terrain Handling**: Different terrains (e.g., asphalt, ice, grass) will affect car behavior.
- **Vehicle Variety**: Players can choose between various vehicle types like boats, hovercrafts, and helicopters.
- **Sound Effects**: Sound elements such as engine noises, crashes, and environmental sounds will enhance immersion.
- **Split-Screen Mode**: Allows two players to compete on the same screen.
- **Ability System**: Optional weapons like missiles or traps can impact opponents or provide a speed boost.

### Usage and Mechanics

- **Controls**: Players use a game controller or keyboard for car control. Each car's speed, ability usage, and response to terrain will vary.
- **Objective**: Players race to the finish line on various tracks, avoiding obstacles and using boosts for speed advantages.

## 2. High-Level Structure of the Software

### Main Modules

- **Game Engine**: Manages physics and game logic.
- **Track Management**: Loads track assets and handles obstacles.
- **Player Module**: Handles player input and character stats.
- **EnemyAI Module**: Manages enemy AI for competitive racing.
- **Physics Module**: Calculates vehicle movement, collisions, and terrain responses.
- **Sound Module**: Manages sound effects and background music.
- **UI Module**: Provides menu navigation and game HUD.

### Main Classes (Initial Outline)

- **Game**: Manages the main game loop, including game state and scene switching.
- **Player**: Represents each player with attributes like position, velocity, weight, and input handling.
- **Enemy**: Represents each enemy, including position, velocity, track-following logic, and interactions with other entities.
- **Car**: Subclass of Player, with properties like handling and speed depending on vehicle type.
- **Track**: Stores track layout, including road, off-road zones, and obstacles.
- **Obstacle**: Represents gameplay-affecting items (oil spills, jams, boosts).
- **SoundManager**: Loads and plays sound effects.
- **UIManager**: Manages user interface elements, split-screen logic, and score display.
- **CameraController**: Controls the camera that follows the player, determining what the player sees on-screen.

## 3. External Libraries

- **[SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/)**: For rendering graphics, audio playback, and input handling in 2D.
- **[Box2D](https://box2d.org/)**: Provides realistic physics calculations for vehicle dynamics and collisions.
- **[IMGUI-SFML](https://github.com/SFML/imgui-sfml)**: Used for creating GUI elements efficiently in menus and the in-game HUD.

## 4. Sprint Plans

### Sprint 1: Basic Project Planning
- **Duration**: 18.10 - 1.11
- **Goals**:
  - Complete the project plan document.
  - Set up the development environment.
  - Define the project schedule.
  - Outline the main class structure.
- **Progress Tracking**:
  - Weekly review meeting on Wednesdays.

### Sprint 2: Initial Implementation
- **Duration**: 1.11 - 15.11
- **Goals**:
  - Set up a basic game loop and initial UI with the main menu.
  - Implement player controls and car physics (basic driving and collisions).
  - Integrate SFML and Box2D, focusing on movement and collision functionality.
  - Design and load track files.
  - Implement terrain types and handling physics for each.
  - Begin incorporating game objects like oil spills and boosts.
- **Progress Tracking**:
  - Weekly review meeting on Wednesdays.
  - Update documentation as progress and changes occur.

### Sprint 3: Enhanced Gameplay Features
- **Duration**: 15.11 - 29.11
- **Goals**:
  - Develop enemy AI for competitive racing.
  - Enhance vehicle movements and controls.
  - Add sound effects for cars, obstacles, and ambient noise.
  - Develop UI components.
  - Implement additional vehicle types (boats, helicopters).
  - Introduce the ability system.
- **Progress Tracking**:
  - Weekly review meeting on Wednesdays.
  - Update documentation based on progress.

### Sprint 4: Polish and Finalize
- **Duration**: 29.11 - 13.12
- **Goals**:
  - Perform bug fixing and testing.
  - Add finishing touches, including ability systems and any additional agreed-upon features.
  - Finalize UI and gameplay flow, ensuring cohesive and debugged elements.
  - Complete final documentation.
- **Progress Tracking**:
  - Weekly review meeting on Wednesdays.
  - Sprint-end meeting to review, gather feedback, and finalize the project.

# Working practices
Each project group is assigned an advisor from the project teaching personnel. 
There will be a dedicated Teams channel for each project topic to facilitate discussion between 
the groups in the same topic and the advisor. 

**The group should meet weekly.** The weekly meeting does not need to be long if there are no special issues 
to discuss, and can be taken remotely as voice/video chat on the group Teams channel (or Zoom or other similar tool), 
preferably at a regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project repository in the `Meeting-notes.md` file. 
    * The commits within the week should have some commit messages referring to the meeting notes so 
      that the project advisor can follow the progress.  
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple of members should be present in each meeting. 
> Regular absence from meetings will affect in individual evaluation.

# Source code documentation
It is strongly recommended to use Doxygen to document your source code.
Please go over the *Project Guidelines* for details.

# TODOs (Date)
You can create a list of TODOs in this file.
The recommended format is:
- Complete class implementation **foo**. Assigned to \<Member 1\>
- Test ...