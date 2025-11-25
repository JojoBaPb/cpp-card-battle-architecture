#pragma once
#include <memory>
#include <iostream>
#include "GameState.h"
#include "Player.h"

class GameEngine {
private:
    // The current state defines how the game behaves right now
    std::unique_ptr<GameState> m_currentState;
    
    // The engine owns the player
    std::unique_ptr<Player> m_player;
  
    // --- NEW: The AI ---
    std::unique_ptr<Player> m_opponent;

    bool m_isRunning;

public:
    GameEngine();

    // Setup the game (Load deck, etc.)
    void Initialize();

    // The Main Loop
    void Run();

    // The Magic: Switch from one state to another
    void ChangeState(std::unique_ptr<GameState> newState);
    
    // Stop the loop
    void Quit() { m_isRunning = false; }

    // Accessors (States need to access the player!)
    Player* GetPlayer() const { return m_player.get(); }

    // --- NEW: Accessor for AI ---
    Player* GetOpponent() const { return m_opponent.get(); }
};
