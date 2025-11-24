#pragma once 
#include <vector>
#include <memory> // Required for smart pointers
#include "Card.h"

// Forward declaration (Critical because PlayCard uses GameEngine&)
class GameEngine; 

class Player {
private:
    // Renamed to m_deck/m_hand to match the .cpp implementation
    std::vector<std::unique_ptr<Card>> m_deck;
    std::vector<std::unique_ptr<Card>> m_hand;

public:
    Player();
    
    // Adds a card to the deck (takes ownership)
    void AddCardToDeck(std::unique_ptr<Card> card);
    
    // Moves a card from deck to hand
    void DrawCard();
    
    // Display current hand
    void ShowHand() const;

    // Shows deck count
    void ShowDeckCount() const;
    
    // Triggers a card's ability (Phase 3 logic)
    void PlayCard(int index, GameEngine& engine); 

    // --- NEW PHASE 4.5 FUNCTIONS (Must be Public!) ---

    // Get a raw pointer to a card in hand (for checking stats without moving it)
    [[nodiscard]] const Card* InspectCard(int index) const;

    // Removes a card from hand and gives ownership to the caller
    [[nodiscard]] std::unique_ptr<Card> PlayCardFromHand(int index);

    // Get current hand size
    [[nodiscard]] size_t GetHandSize() const { return m_hand.size(); }
};
