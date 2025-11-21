#pragma once
#include <string>
#include <iostream>
#include <functional> // Required for storing logic

// Forward declaration
class GameEngine;

// Define a type for ability function
// It takes a reference to the Engine so it can modify the game state
using CardAbility = std::function<void(GameEngine&)>;

class Card {
private:
    std::string m_name;
    int m_cost;
    int m_power;
    std::string m_description;
    
    // The Logic! Default is an empty function (does nothing)
    CardAbility m_onRevealEffect;

public:
    // Updated Constructor to accept an ability
    Card(std::string name, int cost, int power, std::string description, 
         CardAbility ability = nullptr); // Default to null

    virtual ~Card() = default;

    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] int GetCost() const;
    [[nodiscard]] int GetPower() const;
    [[nodiscard]] std::string GetDescription() const;

    virtual void PrintStats() const;

    // Function to trigger the ability
    void Play(GameEngine& engine);
};
