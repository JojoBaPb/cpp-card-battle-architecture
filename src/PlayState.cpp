#include "PlayState.h"
#include "GameEngine.h"
#include "Card.h"
#include <iostream>

void PlayState::Enter(GameEngine& engine) {
    std::cout << "\n[PlayState] Entering... Generating Board.\n";
    
    // 1. Setup the 3 Locations
    // We use reserve to prevent memory re-allocations (Optimization)
    m_locations.reserve(3);
    
    // emplace_back constructs the object directly in the vector (Performance)
    m_locations.emplace_back("The Ruins", "No effect.");
    m_locations.emplace_back("Stark Tower", "At end of turn 5, give all cards here +2 Power.");
    m_locations.emplace_back("Atlantis", "If you have only 1 card here, it has +5 Power.");

    // 2. Setup Player Deck
    Player* player = engine.GetPlayer();
    
    // Create logic for Sherlock
    auto sherlockAbility = [](GameEngine& eng) {
        std::cout << "        [ABILITY] Sherlock sees all...\n";
    };

    player->AddCardToDeck(std::make_unique<Card>("Dracula", 4, 8, "Discard 1 card."));
    player->AddCardToDeck(std::make_unique<Card>("Sherlock", 3, 2, "Reveal Hand.", sherlockAbility));
    player->AddCardToDeck(std::make_unique<Card>("Hulk", 6, 12, "Smash."));
    
    std::cout << "Board and Deck Ready.\n";
}

void PlayState::Update(GameEngine& engine) {
    std::cout << "\n=== GAME BOARD ===\n";
    
    // Print all 3 locations
    for (const auto& loc : m_locations) {
        loc.PrintState();
    }
    std::cout << "==================\n";

    // Simulate Playing a card to the MID location (Index 1)
    std::cout << "\n[Simulation] Playing Hulk to Stark Tower (Middle)...\n";
    
    // Create a temporary Hulk just for this test
    auto hulk = std::make_unique<Card>("Hulk", 6, 12, "Smash.");
    
    // Access location by index [0, 1, 2]
    m_locations[1].AddCard(std::move(hulk));

    // Print the updated middle location
    m_locations[1].PrintState();

    // End the loop
    engine.Quit(); 
}

void PlayState::Exit(GameEngine& engine) {
    std::cout << "[PlayState] Cleaning up Board...\n";
    // Vector clears automatically here. RAII handles it.
}
