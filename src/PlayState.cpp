#include "PlayState.h"
#include "GameEngine.h"
#include "Card.h"
#include "Location.h" 
#include <iostream>
#include <limits> 

void PlayState::Enter(GameEngine& engine) {
    std::cout << "\n[PlayState] Entering... Generating Board.\n";
    
    // 1. Setup Locations
    m_locations.reserve(3);
    m_locations.emplace_back("The Ruins", "No effect.");
    m_locations.emplace_back("Stark Tower", "At end of turn 5, give all cards here +2 Power.");
    m_locations.emplace_back("Atlantis", "If you have only 1 card here, it has +5 Power.");

    // 2. Setup Player Deck (Energy Curve)
    Player* player = engine.GetPlayer();
    
    player->AddCardToDeck(std::make_unique<Card>("Misty Knight", 1, 2, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("Shocker", 2, 3, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("Cyclops", 3, 4, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("The Thing", 4, 6, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("Iron Man", 5, 0, "Ongoing: Double Power."));
    player->AddCardToDeck(std::make_unique<Card>("Hulk", 6, 12, "Smash."));
    
    std::cout << "Deck Ready. Drawing initial hand...\n";

    // Draw initial hand (3 cards)
    player->DrawCard();
    player->DrawCard();
    player->DrawCard();
}

void PlayState::Update(GameEngine& engine) {
    Player* player = engine.GetPlayer();

    // 1. UI HEADER
    std::cout << "\n========================================\n";
    std::cout << "ENERGY: " << player->GetEnergy() << " / " << player->GetMaxEnergy() << "\n";
    std::cout << "========================================\n";

    // 2. Show Board
    for (int i = 0; i < m_locations.size(); ++i) {
        std::cout << "LOC [" << i << "]: "; 
        m_locations[i].PrintState();
    }

    // 3. Show Hand
    player->ShowHand();

    // 4. Input Loop
    int cardIndex = -1;
    int locIndex = -1;

    std::cout << "\n[COMMAND] Enter Card Index (-1 to END TURN, -9 to QUIT): ";
    if (!(std::cin >> cardIndex)) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    // --- QUIT COMMAND ---
    if (cardIndex == -9) {
        engine.Quit();
        return;
    }

    // --- END TURN COMMAND ---
    if (cardIndex == -1) {
        std::cout << ">>> ENDING TURN! <<<\n";
        player->OnTurnStart(); // Logic: Refill Energy, Draw Card
        return; // Start next frame
    }

    // 5. Play Logic
    // A. Validate Card Index
    const Card* cardToInspect = player->InspectCard(cardIndex);
    if (!cardToInspect) {
        std::cout << "[Error] Invalid card index.\n";
        return;
    }

    // B. Validate Energy (The Rules Check)
    if (cardToInspect->GetCost() > player->GetEnergy()) {
        std::cout << "[Rules] Not enough Energy! (Cost: " << cardToInspect->GetCost() 
                  << ", You have: " << player->GetEnergy() << ")\n";
        return; // Stop here
    }

    // C. Get Location
    std::cout << "[COMMAND] Enter Location Index (0-2): ";
    if (!(std::cin >> locIndex)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return; 
    }
    
    if (locIndex < 0 || locIndex >= m_locations.size()) {
        std::cout << "[Error] Invalid Location Index.\n";
        return;
    }

    // D. EXECUTE MOVE
    // Spend Energy FIRST
    player->SpendEnergy(cardToInspect->GetCost());

    // Move Card from Hand to Location
    auto card = player->PlayCardFromHand(cardIndex);
    if (card) {
        bool success = m_locations[locIndex].AddCard(std::move(card));
        if (!success) {
            std::cout << "[Warning] Location Full.\n";
        } else {
            std::cout << "-> Played " << cardToInspect->GetName() << "!\n";
        }
    }
}

void PlayState::Exit(GameEngine& engine) {
    std::cout << "[PlayState] Cleaning up...\n";
}
