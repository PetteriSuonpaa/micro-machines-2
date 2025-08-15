# Micro Machines 2 🚗

A C++ recreation of the classic Micro Machines game.  
The software replicates the original game’s core dynamics including movement, bots, oil spills, boost speed, two maps, and boundaries.  

**Note:** This version does **not** include split-screen, a level editor, or weapons.

---
## 🛠️ Instructions for Building and Running

1. Ensure **SFML** is installed (provided in the repo).  
2. Install **VSCode** with C++ extensions.  
3. Create a folder in a Linux environment:
```bash
mkdir Any_name_you_want
cd Any_name_you_want
```
4. Ensure the repository folder is empty and your SSH key is set up.
5. Clone the repository:
```bash
   git clone git@version.aalto.fi:cabrask1/micro-machines-2.git .
```
6. Build dependencies (Box2D):
```bash
  cd libs/box2d
  mkdir build
  cd build
  cmake ..
  make
```
7. Build the project:
```bash
  cd ~/Any_name_you_want
  mkdir build
  cd build
  cmake ..
  make
  cd ..
  code .

```
8. Start debugging from VSCode.

---
## 🎮 Basic User Guide

Main Menu Navigation: Use arrow keys and Enter.

Game Controls:

Key	Action
↑ Top	Accelerate
↓ Bottom	Decelerate
← Left	Turn left
→ Right	Turn right
Space	Boost

Objective: Complete 3 laps around the racing course.

---
##🧪 Testing

Testing was performed using Google Test.
Focused on verifying all relevant game mechanics and details to ensure correct functionality.

---
## 📝 My Contributions

In this project, I focused on the core gameplay mechanics and user interface elements. My main contributions include:

- Designing and implementing the **main menu**  
- Implementing **track boundaries** to keep gameplay within limits  
- Adding **oil spill mechanics** to affect vehicle movement  
- Collaborating on integrating overall game movement and mechanics
These contributions were crucial to making the game fully playable and faithful to the original Micro Machines experience.

---
## 🔮 Future Improvements

- Add authentication for multiplayer sessions or user profiles

- Add more terrain types and advanced physics

- Implement split-screen mode

- Include a level editor and weapons system

- Expand the audio system and SFX integration

- Optimize code and structure for future expansions
---
## ⚡ Overview

This project was developed collaboratively, but Petteri contributed significantly to:

- Main menu design and implementation

- Boundaries implementation

- Oil spill mechanics

The game successfully replicates the core mechanics of the original Micro Machines game, and it is fully playable on Linux with SFML.

