# Overview

This project is a C++ implementation of the card game [Bohnanza](https://www.youtube.com/watch?v=_fjJ2Hud_o8), a strategic trading and bean farming game. The objective of the game is to grow, trade, and sell bean cards to earn the most coins by the end of the game. This project showcases advanced object-oriented programming concepts and utilizes modern C++ features.

## Run The Program
> [!NOTE]  
> Your C++ compiler must have c++14 support.
```console
# On UNIX (MacOS, Linux)
./play.sh

# On Windows
g++ -std=c++14 src/*.cpp -Iinclude -o Game    # Compile the program to a "Game" executable
Game.exe                                      # Run the executable
```

## Gameplay Features
- **Planting and Harvesting**: Players plant bean cards in fields, harvesting them for coins when enough cards are accumulated.
- **Trading and Negotiation**: Players can trade bean cards with one another to optimize their fields.
- **Deck Management**: Players draw cards from a shared deck and manage discard piles strategically.

## Technical Features
- **Object-Oriented Design**:
  - Implements multiple classes, such as `Card`, `Deck`, `DiscardPile`, `Hand`, `Chain`, `TradeArea`, `Table`, and `Player`, each encapsulating key game mechanics.
- **Inheritance and Polymorphism**:
  - The card system leverages polymorphism for managing different bean types and their behaviours.
- **Factory Design Pattern**:
  - Used for creating and managing bean cards efficiently.
- **Standard Containers**:
  - Utilizes C++ standard containers such as `vector`, `deque`, and `set` for efficient card and game state management.

## Objective
The game ends when the deck is empty, and the player with the most coins wins.

This project demonstrates proficiency in C++ concepts like inheritance, polymorphism, exception handling, templates, and standard library usage while simulating the fun and challenge of the Bohnanza card game.