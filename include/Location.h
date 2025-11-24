#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Card.h"

class Location {
private:
    std::string m_name;
    std::string m_description;
    
    // The Location OWNS the cards placed here
    std::vector<std::unique_ptr<Card>> m_cards;
    
    // Marvel Snap rule: Max 4 cards per location
    const int MAX_CARDS = 4; 

public:
    Location(std::string name, std::string desc);

    // Add a card to this location (Transfer ownership from Hand to Location)
    bool AddCard(std::unique_ptr<Card> card);

    // Calculate total power at this location
    [[nodiscard]] int GetTotalPower() const;
    
    [[nodiscard]] std::string GetName() const { return m_name; }

    // Debug helper to visualize the board
    void PrintState() const;
};
