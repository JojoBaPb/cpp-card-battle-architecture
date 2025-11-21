#pragma once
#include <string>
#include <iostream>

class Card {
private:
    // These variable names MUST match what is in src/Card.cpp
    std::string m_name;
    int m_cost;
    int m_power;
    std::string m_description;

public:
    // Constructor
    Card(std::string name, int cost, int power, std::string description);

    // Virtual Destructor
    virtual ~Card() = default;

    // Getters - marked [[nodiscard]] for safety
    [[nodiscard]] std::string GetName() const;
    [[nodiscard]] int GetCost() const;
    [[nodiscard]] int GetPower() const;
    [[nodiscard]] std::string GetDescription() const;

    // Display stats to console
    virtual void PrintStats() const;
};
