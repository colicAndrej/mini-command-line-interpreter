#include "Engine.h"

int main() {
    unique_ptr<Engine> engine;
    engine = Engine::init();
    engine->run();

    return 0;
}