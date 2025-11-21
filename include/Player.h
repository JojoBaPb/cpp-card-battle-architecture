#pragma once 
#include <vector>
#include <memory> // Required for smart pointers
#include "Card.h"

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
};
