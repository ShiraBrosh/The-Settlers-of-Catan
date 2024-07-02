Certainly! Here's the complete README file in one piece for easy copying:

```markdown
# Catan Game Project

## Project Overview

This project is a C++ implementation of the popular board game "Catan." The game is designed to simulate the original gameplay, including features such as building settlements, roads, cities, and managing development cards.

## About Catan

Catan (formerly known as The Settlers of Catan) is a multiplayer board game designed by Klaus Teuber. In Catan, players assume the roles of settlers, each attempting to build and develop holdings while trading and acquiring resources.

### Game Basics

- **Players**: 3-4 players
- **Game Duration**: Approximately 60-120 minutes
- **Age Range**: 10 years and up

### Gameplay Overview

1. **Setup**: Players build the game board using hexagonal tiles that represent different land types, each producing a specific resource: brick, lumber, ore, grain, or wool.

2. **Resources**: Players collect resource cards based on the dice roll at the beginning of each turn and the position of their settlements and cities.

3. **Building**: Players use their resources to build roads, settlements, and cities, and to buy development cards.

4. **Trading**: Players can trade resources with each other and with the bank.

5. **Development Cards**: These special cards provide various advantages, such as moving the robber, gaining resources, or earning victory points.

6. **Victory Points**: The first player to reach 10 victory points wins the game.

### Key Elements in Our Implementation

- **Resource Management**: Accurate tracking and distribution of resources.
- **Building Mechanics**: Implementation of rules for placing roads, settlements, and cities.
- **Trade System**: Allowing players to trade resources with each other and the bank.
- **Development Cards**: Full implementation of various development card types and their effects.
- **Robber Mechanics**: Handling the robber's movement and its impact on resource production.
- **Victory Condition Checking**: Continuous monitoring of victory points to determine the game's end.

## Features

- **Game Elements**: The project includes classes for different game elements like settlements, roads, cities, and development cards.
- **Player Management**: Supports multiple players with their respective resources and development cards.
- **Game Board**: Implements the game board with tiles, paths, and vertices to place game elements.
- **Development Cards**: Includes various development cards like Knight, Road Building, Year of Plenty, Monopoly, and Victory Points.
- **Game Logic**: Comprehensive game logic to handle player actions, resource management, and victory conditions.
- **Unit Tests**: Includes unit tests to ensure the correctness of the game mechanics.

## File Structure

```
ex3CPP_project/
│
├── ex3CPP/
│   ├── Board.cpp
│   ├── Board.hpp
│   ├── Building.cpp
│   ├── Building.hpp
│   ├── City.cpp
│   ├── City.hpp
│   ├── DevelopmentCard.cpp
│   ├── DevelopmentCard.hpp
│   ├── Katan.cpp
│   ├── Katan.hpp
│   ├── KnightCard.cpp
│   ├── KnightCard.hpp
│   ├── main.cpp
│   ├── makefile
│   ├── MonopolyCard.cpp
│   ├── MonopolyCard.hpp
│   ├── Path.cpp
│   ├── Path.hpp
│   ├── Player.cpp
│   ├── Player.hpp
│   ├── Road.cpp
│   ├── Road.hpp
│   ├── RoadBuildingCard.cpp
│   ├── RoadBuildingCard.hpp
│   ├── Settlement.cpp
│   ├── Settlement.hpp
│   ├── test.cpp
│   ├── Tile.cpp
│   ├── Tile.hpp
│   ├── Vertex.cpp
│   ├── Vertex.hpp
│   ├── VictoryPointCard.cpp
│   ├── VictoryPointCard.hpp
│   ├── YearOfPlentyCard.cpp
│   ├── YearOfPlentyCard.hpp
│   └── .vscode/
│       ├── c_cpp_properties.json
│       └── settings.json
```

## Compilation and Execution

1. **Prerequisites**: Ensure you have a C++ compiler installed (e.g., `g++`), and `make` utility is available.

2. **Build the Project**: Navigate to the `ex3CPP` directory and run the following command:
   ```sh
   make
   ```

3. **Run the Game**: After a successful build, execute the game using:
   ```sh
   ./katan
   ```

## Unit Tests

- The project includes unit tests to verify the correctness of various components.
- Tests are located in `test.cpp`.
- To run the tests:
  ```sh
  make test
  ./test
  ```

## Development Environment

- The project includes configuration files for Visual Studio Code under the `.vscode` directory.
- Ensure to configure your IDE to use these settings for an optimized development experience.

