#include "GameEngine.h"
#include "PlayState.h"

int main() {
    // 1. Create the Engine (The container for everything)
    GameEngine engine;
    
    // 2. Initialize Data
    engine.Initialize();

    // 3. Load the first state (PlayState)
    engine.ChangeState(std::make_unique<PlayState>());

    // 4. Start the Loop
    engine.Run();

    return 0;
}
