#pragma once
#include <string>
#include <iostream>

// Forward declaration (prevents circular dependency)
class GameEngine; 

class GameState {
public:
    virtual ~GameState() = default;

    // Called when entering the state (Setup)
    virtual void Enter(GameEngine& engine) = 0;

    // Called every frame/tick (Logic)
    virtual void Update(GameEngine& engine) = 0;

    // Called when leaving the state (Cleanup)
    virtual void Exit(GameEngine& engine) = 0;

    // For debugging
    [[nodiscard]] virtual std::string GetName() const = 0;
};
