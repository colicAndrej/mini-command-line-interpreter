#include "Engine.h"

Engine::Engine(unique_ptr<Reader> reader): m_reader(move(reader)) {}

unique_ptr<Engine> Engine::init() {
    unique_ptr<ConsoleReader> reader = make_unique<ConsoleReader>();
    unique_ptr<CommandFactory> commandFactory = make_unique<CommandFactory>();
    unique_ptr<Executor> executor = make_unique<Executor>(move(commandFactory));
    unique_ptr<Tokenizer> tokenizer = make_unique<Tokenizer>();
    unique_ptr<Parser> parser = make_unique<Parser>(move(tokenizer));
    Interpreter::init(move(parser), move(executor));

    return unique_ptr<Engine>(new Engine(move(reader)));
}

void Engine::run() {
    while (true) {
        if (m_reader->isConsole())
            cout << prompt << " ";
        string line = m_reader->getNextLine();
        if (m_reader->endOfRead())
            break;
        if (line.empty())
            continue;
        try {
            Interpreter::instance().processLine(line);
            if (m_reader->endOfRead())
                m_reader->reset();
        } catch (const exception& e) {
            cout << e.what() << endl;
            if (m_reader->endOfRead())
                m_reader->reset();
        }
        if (m_reader->isConsole())
            cout << endl;
    }
}
