#include "PlayState.h"
#include "GameEngine.h"
#include "Card.h"
#include "Location.h" 
#include <iostream>
#include <limits> 
#include <cstdlib> // For rand()

// --- 1. AI LOGIC AT THE TOP (GLOBAL SCOPE) ---
// This function MUST be outside PlayState::Enter
void ExecuteAITurn(Player* ai, std::vector<Location>& locations) {
    std::cout << "\n[AI] Thinking...\n";
    
    // AI Start of Turn (Refill Energy)
    ai->OnTurnStart();

    // Strategy: Try to play cards backwards (Expensive first)
    for (int i = ai->GetHandSize() - 1; i >= 0; --i) {
        const Card* card = ai->InspectCard(i);
        
        // Can AI afford it?
        if (card && card->GetCost() <= ai->GetEnergy()) {
            
            // Pick a random location (0, 1, or 2)
            int targetLoc = std::rand() % 3;
            
            // Spend Energy
            ai->SpendEnergy(card->GetCost());
            
            // Move Card
            auto cardObj = ai->PlayCardFromHand(i);
            
            // Add to location
            if (locations[targetLoc].AddCard(std::move(cardObj))) {
                std::cout << "[AI] Played " << card->GetName() << " to Location " << targetLoc << "!\n";
            }
        }
    }
}

// --- 2. CLASS METHODS START HERE ---

void PlayState::Enter(GameEngine& engine) {
    std::cout << "\n[PlayState] Entering... Generating Board.\n";
    
    // Setup Locations
    m_locations.reserve(3);
    m_locations.emplace_back("The Ruins", "No effect.");
    m_locations.emplace_back("Stark Tower", "At end of turn 5, give all cards here +2 Power.");
    m_locations.emplace_back("Atlantis", "If you have only 1 card here, it has +5 Power.");

    // --- SETUP HUMAN PLAYER ---
    Player* player = engine.GetPlayer();
    player->AddCardToDeck(std::make_unique<Card>("Misty Knight", 1, 2, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("Shocker", 2, 3, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("Cyclops", 3, 4, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("The Thing", 4, 6, "No Ability."));
    player->AddCardToDeck(std::make_unique<Card>("Iron Man", 5, 0, "Ongoing: Double Power."));
    player->AddCardToDeck(std::make_unique<Card>("Hulk", 6, 12, "Smash."));
    
    // Draw initial human hand
    player->DrawCard();
    player->DrawCard();
    player->DrawCard();

    // --- SETUP AI PLAYER ---
    Player* ai = engine.GetOpponent();
    ai->AddCardToDeck(std::make_unique<Card>("Squirrel", 1, 2, ""));
    ai->AddCardToDeck(std::make_unique<Card>("Ant-Man", 1, 1, ""));
    ai->AddCardToDeck(std::make_unique<Card>("Cyclops", 3, 4, ""));
    ai->AddCardToDeck(std::make_unique<Card>("Abomination", 5, 9, ""));
    ai->AddCardToDeck(std::make_unique<Card>("Hulk", 6, 12, ""));

    // Draw initial AI hand
    ai->DrawCard();
    ai->DrawCard();
    ai->DrawCard();

    std::cout << "Board Ready. Game Start!\n";
}

void PlayState::Update(GameEngine& engine) {
    Player* player = engine.GetPlayer();

    // UI HEADER
    std::cout << "\n========================================\n";
    std::cout << "ENERGY: " << player->GetEnergy() << " / " << player->GetMaxEnergy() << "\n";
    std::cout << "========================================\n";

    // Show Board
    for (int i = 0; i < m_locations.size(); ++i) {
        std::cout << "LOC [" << i << "]: "; 
        m_locations[i].PrintState();
    }

    // Show Hand
    player->ShowHand();

    // Input Loop
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
        std::cout << ">>> ENDING PLAYER TURN! <<<\n";
        
        // 1. Human Logic (Refill Energy)
        player->OnTurnStart(); 

        // 2. TRIGGER AI TURN
        Player* ai = engine.GetOpponent();
        ExecuteAITurn(ai, m_locations);

        return; // Start next frame
    }

    // Play Logic (Human)
    const Card* cardToInspect = player->InspectCard(cardIndex);
    if (!cardToInspect) {
        std::cout << "[Error] Invalid card index.\n";
        return;
    }

    if (cardToInspect->GetCost() > player->GetEnergy()) {
        std::cout << "[Rules] Not enough Energy! (Cost: " << cardToInspect->GetCost() 
                  << ", You have: " << player->GetEnergy() << ")\n";
        return; 
    }

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

    player->SpendEnergy(cardToInspect->GetCost());

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
