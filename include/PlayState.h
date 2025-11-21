#pragma once
#include "GameState.h"

class PlayState : public GameState {
public:
    void Enter(GameEngine& engine) override;
    void Update(GameEngine& engine) override;
    void Exit(GameEngine& engine) override;
    
    [[nodiscard]] std::string GetName() const override { return "Play State"; }
};
