#pragma once 
#include <vector>
#include <memory> // Required for smart pointers
#include "Card.h"

// Forward declaration (Critical because PlayCard uses GameEngine&)
class GameEngine; 

class Player {
private:
    // Memory Management: The Player OWNS these cards.
    std::vector<std::unique_ptr<Card>> m_deck;
    std::vector<std::unique_ptr<Card>> m_hand;

    // --- Energy System (Phase 5) ---
    int m_currentEnergy = 1;
    int m_maxEnergy = 1; // Starts at 1, increases by 1 each turn (max 6)

public:
    Player();
    
    // --- Deck & Hand Management ---
    
    // Adds a card to the deck (takes ownership)
    void AddCardToDeck(std::unique_ptr<Card> card);
    
    // Moves a card from deck to hand
    void DrawCard();
    
    // Display current hand to console
    void ShowHand() const;

    // Shows deck count to console
    void ShowDeckCount() const;
    
    // --- Card Interaction (Phase 3 & 4) ---

    // Get a raw pointer to a card in hand (for checking stats/cost without moving it)
    // Returns nullptr if index is invalid
    [[nodiscard]] const Card* InspectCard(int index) const;

    // Removes a card from hand and gives ownership to the caller (The Board/Location)
    // Returns nullptr if index is invalid
    [[nodiscard]] std::unique_ptr<Card> PlayCardFromHand(int index);

    // Get current hand size
    [[nodiscard]] size_t GetHandSize() const { return m_hand.size(); }
    
    // Triggers a card's ability (Legacy/Direct interaction)
    void PlayCard(int index, GameEngine& engine); 

    // --- Energy System (Phase 5) ---
    
    [[nodiscard]] int GetEnergy() const { return m_currentEnergy; }
    [[nodiscard]] int GetMaxEnergy() const { return m_maxEnergy; }
    
    // Attempt to spend energy. Returns true if successful (enough energy).
    bool SpendEnergy(int amount);
    
    // Called at start of a new turn (Refills energy, draws card)
    void OnTurnStart();
};
