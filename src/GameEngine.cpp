#include "GameEngine.h"

// Will implement specific states later, but need the header structure ready.
// For now,implementation of Engine logic.

GameEngine::GameEngine() : m_isRunning(true) {
    m_player = std::make_unique<Player>();

    // --- NEW: Initialize AI ---
    m_opponent = std::make_unique<Player>();  
}

void GameEngine::Initialize() {
    std::cout << "[Engine] Initializing...\n";
    
    // Setup Player Deck
    // Move the deck creation logic here later.
    // Ensure the player exists.
    if (m_player) {
        std::cout << "[Engine] Player system ready.\n";
    }
}

void GameEngine::ChangeState(std::unique_ptr<GameState> newState) {
    // 1. Exit the current state (if it exists)
    if (m_currentState) {
        m_currentState->Exit(*this);
    }

    // 2. Switch ownership
    m_currentState = std::move(newState);

    // 3. Enter the new state
    if (m_currentState) {
        std::cout << "--- State Changed to: " << m_currentState->GetName() << " ---\n";
        m_currentState->Enter(*this);
    }
}

void GameEngine::Run() {
    std::cout << "[Engine] Starting Game Loop.\n";
    
    while (m_isRunning) {
        if (m_currentState) {
            m_currentState->Update(*this);
        } else {
            // If no state, exit to prevent infinite empty loop
            std::cout << "[Engine] No state loaded. Quitting.\n";
            m_isRunning = false;
        }
    }
    std::cout << "[Engine] Game Over.\n";
}
