#pragma once
#include <vector>
#include "GameState.h"
#include "Location.h" 

class PlayState : public GameState {
private:
    // The Board! (Holds 3 locations)
    std::vector<Location> m_locations;

public:
    void Enter(GameEngine& engine) override;
    void Update(GameEngine& engine) override;
    void Exit(GameEngine& engine) override;
    
    [[nodiscard]] std::string GetName() const override { return "Play State"; }
};
