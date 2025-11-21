#include "PlayState.h"
#include "GameEngine.h"
#include "Card.h"
#include <iostream>

void PlayState::Enter(GameEngine& engine) {
    std::cout << "\n[PlayState] Entering... Preparing Deck.\n";
    Player* player = engine.GetPlayer();

    // --- Card 1: Dracula (Logic pending...) ---
    auto c1 = std::make_unique<Card>("Dracula", 4, 8, "Discard 1 card to play.");

    // --- Card 2: Sherlock Holmes (WITH LOGIC!) ---
    // We use a Lambda Function ( [](){} ) to define behavior inline
    auto sherlockAbility = [](GameEngine& eng) {
        std::cout << "       [ABILITY] Sherlock scans the opponent...\n";
        std::cout << "       [ABILITY] (Mockup) Opponent has: Green Goblin, Thanos.\n";
    };

    auto c2 = std::make_unique<Card>(
        "Sherlock Holmes", 3, 2, "On Reveal: View opponent hand.", sherlockAbility
    );

    // --- Card 3: Frankenstein (No Ability) ---
    auto c3 = std::make_unique<Card>("Frankenstein", 6, 12, "No Ability.");

    // Note: Stack Order! Last added is First drawn.
    // Adding Sherlock LAST so we draw him FIRST to test the ability.
    player->AddCardToDeck(std::move(c1));
    player->AddCardToDeck(std::move(c3));
    player->AddCardToDeck(std::move(c2)); // Sherlock is now on top

    player->ShowDeckCount();
}

void PlayState::Update(GameEngine& engine) {
    std::cout << "\n[PlayState] UPDATE: Player taking action...\n";
    Player* player = engine.GetPlayer();
    
    // 1. Draw Sherlock
    player->DrawCard();
    
    // 2. "Play" the card to trigger the event
    // (In a real game, we'd pick from hand. Here we are just hacking it to test)
    // We need to access the card we just drew. 
    // Note: We need a getter for the hand in Player.h to do this properly, 
    // but for now, let's just assume the player plays the last card they drew.
    
    // We need to implement PlayCard() in Player.h to make this clean.
    // For now, we're just demonstrating drawing.
    player->ShowHand();

    std::cout << "[PlayState] Turn complete. Ending demo.\n";
    engine.Quit(); 
}
