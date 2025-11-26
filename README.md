# C++ Card Battler Engine (Portfolio Project)

*link to a GIF of console running a turn)*

A high-performance, text-based game engine implementing a **Finite State Machine (FSM)** and **Data-Driven Architecture** in **C++20**.

This project replicates the complex core mechanics of *Marvel Snap* (Energy system, 3-lane board, simultaneous resolution) to demonstrate strict memory management, RAII principles, and scalable software architecture without the overhead of a graphical engine.

  * **Role:** Systems Engineer / Gameplay Programmer
  * **Language:** C++20
  * **Build System:** CMake
  * **Platform:** Linux / WSL / macOS

-----

## 🚀 Key Features

  * **Finite State Machine (FSM):** Implements the State Pattern to decouple game flow (Initialize → PlayState → Resolution), preventing the "god object" anti-pattern in the game loop.
  * **RAII & Memory Safety:** Strict ownership semantics using `std::unique_ptr`. Cards are ownership-transferred from `Deck` → `Hand` → `Location` ensuring zero memory leaks.
  * **Data-Driven Abilities:** Card logic (e.g., "On Reveal") is decoupled from the class hierarchy using `std::function` and Lambda expressions. This prevents inheritance bloat and allows for runtime ability composition.
  * **Heuristic AI:** Integrated an AI opponent that evaluates energy curves and randomizes board placement based on available slots.

-----

## 🛠️ Architecture & Code Samples

### 1\. Memory Ownership (RAII)

The engine strictly avoids raw pointers for ownership. A card is never "copied"; it is moved through the memory pipeline.

```cpp
// Example: Transferring ownership from Hand to Board
// The 'Hand' vector loses the pointer, the 'Location' vector gains it.
std::unique_ptr<Card> card = player->PlayCardFromHand(index);
location.AddCard(std::move(card));
```

### 2\. Functional Event System (Composition over Inheritance)

Instead of creating a subclass for every card (e.g., `class Sherlock : public Card`), abilities are injected as functional objects. This aligns with Entity-Component-System (ECS) philosophies used in modern engines.

```cpp
// Data-Driven definition of a card ability
auto visionAbility = [](GameEngine& engine) {
    std::cout << "[Ability] Vision can move to any location!\n";
};

// Logic is passed as data into the constructor
auto card = std::make_unique<Card>("Vision", 5, 7, "Move", visionAbility);
```

### 3\. The State Pattern

Game logic is encapsulated in discrete states.

  * `GameEngine`: The context holder. Owns the Players and the current State.
  * `GameState` (Interface): Defines `Enter`, `Update`, `Exit`.
  * `PlayState`: Handles the active gameplay loop, input parsing, and AI triggers.

-----

## ⚖️ Design Trade-offs

  * **Lambdas vs. Virtual Functions:** I chose `std::function` for abilities to keep the `Card` class lightweight. While this adds a small overhead compared to a direct virtual function call, it dramatically increases flexibility for designers to create new card types without recompiling the engine core.
  * **Text-Based vs. Graphical:** I prioritized a console implementation to focus entirely on **architecture, memory management, and game logic** without the distraction of rendering pipelines. This allowed for faster iteration on the core simulation algorithms.

-----

## 💻 Build Instructions

This project uses CMake and requires a C++ compiler supporting C++17 or higher.

```bash
mkdir build
cd build
cmake ..
make
./CardBattleEngine
```

-----

## 🔮 Future Roadmap

  * **Serialization:** Loading card definitions from JSON files to fully separate data from code.
  * **Event Bus:** Implementing a complete Observer pattern for complex card interactions (e.g., "When *any* card is destroyed, trigger X").
  * **Networking:** Separating the Client and Server logic for authoritative multiplayer support.

-----

## 📄 License

This project is open-source under the MIT License.
*Note: References to 'Marvel Snap' mechanics are for educational replication purposes only.*
