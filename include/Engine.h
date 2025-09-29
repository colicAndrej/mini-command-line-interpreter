#ifndef ENGINE_H
#define ENGINE_H

#include "Interpreter.h"

class Engine {
    //reads input from a console and uses Interpreter class to interpret it
    unique_ptr<Reader> m_reader;
    Engine(unique_ptr<Reader> reader);

public:
    static unique_ptr<Engine> init();
    void run();
};

#endif //ENGINE_H