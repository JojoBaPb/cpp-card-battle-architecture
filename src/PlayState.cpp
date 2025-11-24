#include "PlayState.h"
#include "GameEngine.h"
#include "Card.h"
#include "Location.h" 
#include <iostream>
#include <limits> // Required for clearing input buffer

void PlayState::Enter(GameEngine& engine) {
    std::cout << "\n[PlayState] Entering... Generating Board.\n";
    
    // 1. Setup the 3 Locations
    m_locations.reserve(3);
    m_locations.emplace_back("The Ruins", "No effect.");
    m_locations.emplace_back("Stark Tower", "At end of turn 5, give all cards here +2 Power.");
    m_locations.emplace_back("Atlantis", "If you have only 1 card here, it has +5 Power.");

    // 2. Setup Player Deck
    Player* player = engine.GetPlayer();
    
    // Create logic for Sherlock
    auto sherlockAbility = [](GameEngine& eng) {
        std::cout << "         [ABILITY] Sherlock sees all...\n";
    };

    // Add cards to deck
    player->AddCardToDeck(std::make_unique<Card>("Dracula", 4, 8, "Discard 1 card."));
    player->AddCardToDeck(std::make_unique<Card>("Sherlock", 3, 2, "Reveal Hand.", sherlockAbility));
    player->AddCardToDeck(std::make_unique<Card>("Hulk", 6, 12, "Smash."));
    
    std::cout << "Deck Ready. Drawing initial hand...\n";

    // Draws cards so your hand is not empty.
    player->DrawCard();
    player->DrawCard();
    player->DrawCard();
}

void PlayState::Update(GameEngine& engine) {
    // 1. Clear screen separator
    std::cout << "\n========================================\n";

    // 2. Show Board
    for (int i = 0; i < m_locations.size(); ++i) {
        // Simple visual divider for locations
        std::cout << "LOC [" << i << "]: "; 
        m_locations[i].PrintState();
    }

    // 3. Show Hand
    Player* player = engine.GetPlayer();
    player->ShowHand();

    // 4. Get User Input
    int cardIndex = -1;
    int locIndex = -1;

    std::cout << "\n[COMMAND] Enter Card Index to play (-1 to Quit): ";
    if (!(std::cin >> cardIndex)) {
        // Handle garbage input (non-numbers)
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Try again.\n";
        return; // Skip this frame
    }

    if (cardIndex == -1) {
        engine.Quit();
        return;
    }

    std::cout << "[COMMAND] Enter Location Index (0-2): ";
    if (!(std::cin >> locIndex)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return; 
    }

    // 5. Execute Logic
    // Validate Location Index
    if (locIndex < 0 || locIndex >= m_locations.size()) {
        std::cout << "[Error] Invalid Location Index!\n";
        return;
    }

    // Try to take the card from hand
    auto card = player->PlayCardFromHand(cardIndex);
    if (card) {
        // Optional: Trigger "On Reveal" ability here!
        // card->Play(engine); 

        // Try to add it to the location
        bool success = m_locations[locIndex].AddCard(std::move(card));
        
        if (!success) {
            std::cout << "[Warning] Card fizzled (Location full).\n";
            // In a real game, you would put it back in hand here.
        } else {
            std::cout << "-> Card played successfully!\n";
        }
    }
}

void PlayState::Exit(GameEngine& engine) {
    std::cout << "[PlayState] Cleaning up...\n";
}
