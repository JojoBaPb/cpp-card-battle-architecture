#include "Player.h"
#include <iostream>

Player::Player() {
    // Reserve memory to prevent re-allocations
    m_deck.reserve(20);
    m_hand.reserve(10);
}

void Player::AddCardToDeck(std::unique_ptr<Card> card) {
    if (card) {
        m_deck.push_back(std::move(card));
    }
}

void Player::DrawCard() {
    if (m_deck.empty()) {
        std::cout << "[System] Deck is empty! Cannot draw.\n";
        return;
    }

    // Move logic: Deck -> Hand
    m_hand.push_back(std::move(m_deck.back()));
    m_deck.pop_back();
}

void Player::ShowHand() const {
    std::cout << "\n--- Current Hand ---\n";
    if (m_hand.empty()) {
        std::cout << "(Empty)\n";
    } else {
        for (const auto& card : m_hand) {
            card->PrintStats();
        }
    }
    std::cout << "--------------------\n";
}

void Player::ShowDeckCount() const {
    std::cout << "[System] Deck Size: " << m_deck.size() << "\n";
}
