#include "Location.h"
#include <iostream>

Location::Location(std::string name, std::string desc)
    : m_name(std::move(name)), m_description(std::move(desc)) 
{
    // Reserve memory to avoid re-allocations
    m_cards.reserve(MAX_CARDS);
}

bool Location::AddCard(std::unique_ptr<Card> card) {
    if (m_cards.size() >= MAX_CARDS) {
        std::cout << "[Location] " << m_name << " is full! Cannot play " << card->GetName() << ".\n";
        return false;
    }
    
    // In the future, we will trigger "On Reveal" effects here.
    m_cards.push_back(std::move(card));
    return true;
}

int Location::GetTotalPower() const {
    int total = 0;
    for (const auto& card : m_cards) {
        total += card->GetPower();
    }
    return total;
}

void Location::PrintState() const {
    std::cout << "+--- " << m_name << " (Total: " << GetTotalPower() << ") ---+\n";
    std::cout << "| Effect: " << m_description << "\n";
    
    if (m_cards.empty()) {
        std::cout << "| (Empty)\n";
    } else {
        for (const auto& card : m_cards) {
            std::cout << "| - " << card->GetName() << " [" << card->GetPower() << "]\n";
        }
    }
    std::cout << "+----------------------------------+\n";
}
