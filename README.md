# VOID's LAST STAND

VOID's LAST STAND is a 2D top-down shooter game built using **SFML** (Simple and Fast Multimedia Library). The player must survive waves of enemies while managing their health, shooting accuracy, and evasion skills. The goal is to achieve the highest possible score by defeating enemies before being overrun.

---

## Features
- **Dynamic Gameplay**: Real-time movement, shooting, and enemy AI.
- **Player Mechanics**:
  - Health bar and collision detection.
  - Precise mouse-controlled aiming.
  - Smooth movement clamped within game boundaries.
- **Enemies**:
  - Randomized spawn locations.
  - Collision detection with the player and other enemies.
  - Health and destructibility.
- **Weapons**:
  - Player can shoot bullets with customizable intervals.
  - Collisions between bullets and enemies.
- **Audio**:
  - Laser firing sounds.
  - Enemy destruction sound effects.
- **Game States**:
  - Main Menu with instructions.
  - Pause and Resume functionality.
- **UI**:
  - Dynamic score display.
  - Timer to track survival duration.
  - Health bar and labels for clarity.

---

## Gameplay
1. **Main Menu**:
   - Press **Enter** to start the game.
   - Press **Escape** to quit.
2. **Controls**:
   - **Mouse Left-Click**: Shoot bullets.
   - **Mouse Movement**: Aim the player's weapon.
   - **Escape**: Pause or resume the game.
3. **Survival**:
   - Survive as long as possible by avoiding enemies and keeping your health above 0.
   - Shoot enemies to gain points.

---

## Installation and Usage
### Prerequisites
- **SFML**: Ensure SFML is installed on your system. [Install SFML](https://www.sfml-dev.org/download.php)
- **Compiler**: A C++ compiler supporting C++11 or later.

### Clone the repository:
   ```bash
   git clone git@github.com:Abubakkar-Khan/VOID-S_LAST_STAND.git
   ```


---

## File Structure
```
VOID's LAST STAND
├── Assets/
│   ├── Textures/
│   │   ├── player.png
│   │   ├── enemy.png
│   │   └── cursor.png
│   ├── Sounds/
│   │   ├── laser.wav
│   │   └── explode.mp3
│   └── Fonts/
│       └── V.ttf
├── src/
│   ├── main.cpp
│   ├── Player.h / Player.cpp
│   ├── Bullet.h / Bullet.cpp
│   ├── Enemy.h / Enemy.cpp
│   ├── HealthBar.h / HealthBar.cpp
│   ├── Collider.h / Collider.cpp
│   ├── Animation.h / Animation.cpp
├── README.md
└── LICENSE
```

---

## Dependencies
- **SFML** (2.5.1 or later):
  - Graphics, Audio, and Window modules.

---

## Contributions
Contributions are welcome! Feel free to fork the repository and submit pull requests for improvements, bug fixes, or new features.

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Screenshots
Add some screenshots or gameplay GIFs to showcase your game.

