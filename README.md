# SFML Chess Engine (C++)

## Overview

SFML Chess Engine is a desktop chess application developed using C++ and SFML (Simple and Fast Multimedia Library). The project provides an interactive graphical chessboard where players can play chess using standard chess rules and piece movements. It demonstrates object-oriented programming, game development concepts, and graphical user interface design in C++.

---

## Features

* Interactive chessboard with graphical interface
* Standard chess piece movement
* Turn-based gameplay
* Move validation
* Piece capturing
* Visual board representation using SFML
* Clean and modular C++ code structure
* Easy to extend with advanced chess features

---

## Technologies Used

### Programming Language

* C++

### Graphics Library

* SFML (Simple and Fast Multimedia Library)

### Development Tools

* Visual Studio Code
* Git
* GitHub

---

## Project Structure

```text
SFML-Chess-Engine-CPP/
│
├── assets/
│   ├── pieces/
│   └── board/
│
├── src/
│   ├── main.cpp
│   ├── Board.cpp
│   ├── Board.h
│   ├── Piece.cpp
│   ├── Piece.h
│   └── ...
│
├── README.md
└── LICENSE
```

---

## Installation

### Prerequisites

* C++ Compiler (GCC, MinGW, or MSVC)
* SFML Library
* Git

### Clone Repository

```bash
git clone https://github.com/priyanshi17112007/SFML-Chess-Engine-CPP.git
cd SFML-Chess-Engine-CPP
```

### Build and Run

1. Install SFML.
2. Configure SFML include and library paths.
3. Compile the source files.
4. Run the executable.

Example (g++):

```bash
g++ src/*.cpp -o ChessGame -lsfml-graphics -lsfml-window -lsfml-system
./ChessGame
```

---

## How to Play

1. Launch the application.
2. Select a chess piece using the mouse.
3. Click on a valid destination square.
4. Play alternately between White and Black.
5. Capture opponent pieces and follow standard chess rules.

## Learning Objectives

This project helped in understanding:

* Object-Oriented Programming (OOP)
* Game Development Fundamentals
* Event Handling in SFML
* Graphics Rendering
* Data Structures and Algorithms
* Git and GitHub Version Control

---

## Future Enhancements

* Check Detection
* Checkmate Detection
* Castling
* En Passant
* Pawn Promotion
* Move History
* Undo/Redo Moves
* Chess Clock
* Save and Load Games
* Multiplayer Support
* AI Opponent using Minimax Algorithm
* Alpha-Beta Pruning Optimization
* Opening Book Support
* PGN Export/Import

---

## Author

=======Priyanshi Sharma============

** C/C++ Developer
** Front-End Development Intern
** Agentic AI Enthusiast

GitHub:
https://github.com/priyanshi17112007

---

## License

This project is open source and available under the MIT License.

