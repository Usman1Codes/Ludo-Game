# Ludo Game in C++ with Raylib

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A classic Ludo board game implemented in C++ using the **Raylib** library for graphics and **pthreads** for multithreaded gameplay. This project supports up to 4 players and brings the traditional Ludo experience to your computer.

---

## 📸 Gameplay Screenshot

*(A screenshot of the game in action would be great here!)*

![Gameplay Screenshot](https://placehold.co/600x400?text=Ludo+Gameplay+Screenshot)

---

## ✨ Features

-   **Graphical Interface**: Built with the simple and easy-to-use Raylib library.
-   **Multiplayer Support**: Play with up to 4 human players on the same machine.
-   **Multithreaded Gameplay**: Uses pthreads to manage player turns and game logic concurrently.
-   **Complete Ludo Rules**: Implements standard Ludo rules, including dice rolling, token movement, capturing opponent tokens, and reaching the home area.
-   **Interactive Controls**: Players use keyboard inputs to roll the dice and move their tokens.

---

## ⚙️ Installation and Execution

Follow these steps to compile and run the game on a Debian-based Linux distribution (like Ubuntu).

### 1. Install Dependencies

First, install the essential tools and libraries required for compilation.

```bash
sudo apt update
sudo apt install build-essential git cmake libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

### 2. Install Raylib

Next, clone the Raylib repository and install it from the source.

```bash
# Clone the official Raylib repository
git clone https://github.com/raysan5/raylib.git

# Navigate into the source directory
cd raylib/src/

# Build and install the static library
make PLATFORM=PLATFORM_DESKTOP
sudo make install

# Go back to your original project directory
cd ../../
```

### 3. Compile and Run the Game

Finally, compile the Ludo game source code and run the executable.

```bash
# Compile the game
g++ ludo.cpp -o ludo -lraylib -lpthread

# Run the game
./ludo
```

---

## 룰 How to Play

1.  Run the game executable.
2.  The game will start with 4 players: Red, Green, Yellow, and Blue.
3.  Players take turns rolling the dice by pressing the designated key.
4.  To get a token out of the starting house, you must roll a **6**.
5.  Use the number keys (1-4) to choose which token to move.
6.  The goal is to get all your tokens around the board and into your home column.
7.  You can capture an opponent's token by landing on the same square, sending it back to their starting house.

---

## 📂 Project Structure

```
OS-PROJECT-main/
├── ludo.cpp          # Main game logic, rendering, and thread management
├── token.h           # Header file for the Token class
├── token.cpp         # Implementation of the Token class
├── README.md         # This file
└── ...               # Other project files
```

---

## 📄 License

This project is licensed under the MIT License. See the LICENSE file for details.

