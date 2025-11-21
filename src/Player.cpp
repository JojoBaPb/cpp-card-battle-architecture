#include "Player.h"
#include <iostream>
#include "GameEngine.h"

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

void Player::PlayCard(int index, GameEngine& engine) {
    if (index < 0 || index >= m_hand.size()) {
        std::cout << "[Error] Invalid card index.\n";
        return;
    }

    // 1. Get the card
    // unique_ptr means we own it. We need to decide if playing destroys it or moves it to board.
    // For now, let's just access it and trigger the effect.
    Card* cardToPlay = m_hand[index].get();
    
    // 2. Trigger Logic
    cardToPlay->Play(engine);

    // 3. (Optional) Remove from hand? 
    // In Marvel Snap, it goes to the board. We don't have a board yet.
    // So let's leave it in hand for this phase.
}
