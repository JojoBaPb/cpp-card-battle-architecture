#include "Card.h"

// Constructor
Card::Card(std::string name, int cost, int power, std::string description)
    : m_name(std::move(name)), m_cost(cost), m_power(power), m_description(std::move(description)) 
{
}

std::string Card::GetName() const { return m_name; }
int Card::GetCost() const { return m_cost; }
int Card::GetPower() const { return m_power; }
std::string Card::GetDescription() const { return m_description; }

void Card::PrintStats() const {
    std::cout << "   [" << m_cost << "] " << m_name << " (Power: " << m_power << ")\n"
              << "       Desc: " << m_description << "\n";
}
