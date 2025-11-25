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
    
    // 1. Sum up the base power of all cards
    for (const auto& card : m_cards) {
        total += card->GetPower();
    }

    // 2. Apply Location Specific Modifiers
    // In a real engine, we'd use inheritance (class Atlantis : public Location)
    // But for this portfolio prototype, simple logic checks work perfectly.

    // --- ATLANTIS LOGIC ---
    if (m_name == "Atlantis") {
        if (m_cards.size() == 1) {
            // "If you have only 1 card here, it has +5 Power."
            total += 5; 
        }
    }

    // --- STARK TOWER LOGIC (Simple version) ---
    // (Real logic requires knowing Turn Number, which we don't pass here yet)
    // Let's just say it gives +1 to everyone for testing
    if (m_name == "Stark Tower") {
        // e.g. total += m_cards.size(); 
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
