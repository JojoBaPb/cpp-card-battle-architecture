# C++ Card Battler Engine

A high-performance, text-based game engine implementing a **Finite State Machine (FSM)** and **Data-Driven Architecture**. This project replicates the core mechanics of *Marvel Snap* (Energy system, 3-lane board, simultaneous turns) to demonstrate strict memory management and clean software architecture in C++20.

**Role:** Systems Engineer / Gameplay Programmer  
**Language:** C++20  
**Build System:** CMake  

---

## 🚀 Key Features

* **Finite State Machine (FSM):** Implements the State Pattern to manage game flow (`Initialize` → `PlayState` → `Resolution`).
* **RAII & Memory Safety:** Strict ownership semantics using `std::unique_ptr`. Cards are ownership-transferred from `Deck` → `Hand` → `Location` without memory leaks.
* **Data-Driven Abilities:** Card logic (e.g., "On Reveal") is decoupled from the class hierarchy using `std::function` and Lambda expressions, allowing for flexible ability creation without inheritance bloat.
* **Resource Management:** Implemented a scalable Energy system and turn-based progression logic.
* **AI Opponent:** Integrated a heuristic-based AI that evaluates energy cost and randomizes board placement.

---

## 🛠️ Architecture Overview

### 1. Memory Ownership (RAII)
The engine strictly avoids raw pointers for ownership. A card is never "copied"; it is moved.

```cpp
// Example: Transferring ownership from Hand to Board
std::unique_ptr<Card> card = player->PlayCardFromHand(index);
location.AddCard(std::move(card));
```

### 2. The State Pattern
Game logic is encapsulated in discrete states to prevent "spaghetti code" in the main loop.

* **GameEngine:** The context holder. Owns the Players and the current State.
* **GameState (Interface):** Defines `Enter`, `Update`, `Exit`.
* **PlayState:** Handles the active gameplay loop, input parsing, and AI triggers.

### 3. Functional Event System
Instead of creating a subclass for every card (e.g., `class Sherlock : public Card`), abilities are injected as functional objects.

```cpp
// Data-Driven definition of a card ability
auto visionAbility = [](GameEngine& engine) {
    std::cout << "[Ability] Vision can move to any location!\n";
};

// Logic is passed as data
auto card = std::make_unique<Card>("Vision", 5, 7, "Move", visionAbility);
```

---

## 💻 Build Instructions

This project uses **CMake** and requires a C++ compiler supporting C++17 or higher.

### Linux / WSL / macOS
```bash
mkdir build
cd build
cmake ..
make
./CardBattleEngine
```

---

## 🔮 Future Roadmap

* **Serialization:** Loading card definitions from JSON files instead of hard-coding.
* **Event Bus:** Implementing a complete Observer pattern for complex card interactions (e.g., "When a card is destroyed...").
* **Networking:** Separating the Client and Server logic for multiplayer support.

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).  
*Note: Character names (Dracula, Sherlock Holmes) are Public Domain. References to 'Marvel Snap' mechanics are for educational replication purposes only.*
