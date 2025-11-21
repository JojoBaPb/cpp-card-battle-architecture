#include "PlayState.h"
#include "GameEngine.h"
#include "Card.h"
#include <iostream>

void PlayState::Enter(GameEngine& engine) {
    std::cout << "\n[PlayState] Entering... Preparing Deck.\n";

    // Access the player through the engine
    Player* player = engine.GetPlayer();

    // 1. Setup Deck (The Invincible Roster)
    auto c1 = std::make_unique<Card>("Dracula", 4, 8, "Discard 1 card to play.");
    auto c2 = std::make_unique<Card>("Sherlock Holmes", 3, 2, "Reveal Opponent Hand.");
    auto c3 = std::make_unique<Card>("Frankenstein", 6, 12, "No Ability.");

    player->AddCardToDeck(std::move(c1));
    player->AddCardToDeck(std::move(c2));
    player->AddCardToDeck(std::move(c3));

    player->ShowDeckCount();
}

void PlayState::Update(GameEngine& engine) {
    // This function runs inside the game loop!
    
    std::cout << "\n[PlayState] UPDATE: Player taking action...\n";
    
    Player* player = engine.GetPlayer();
    
    // Draw a card
    player->DrawCard();
    player->ShowHand();

    // Simple logic to end the demo so it doesn't loop forever
    std::cout << "[PlayState] Turn complete. Ending demo.\n";
    engine.Quit(); 
}

void PlayState::Exit(GameEngine& engine) {
    std::cout << "[PlayState] Cleaning up...\n";
}
