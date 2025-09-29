#ifndef INTEPRETER_H
#define INTEPRETER_H

#include "Executor.h"
#include "Writer.h"

class Executor;
class CommandBatch;

struct OutputInfo {
    string filename = "";
    bool redirectOut = false;
    bool add = false;
};

class Interpreter {
    //singleton Interpreter class that interprets a single line
    unique_ptr<Parser> m_parser;
    unique_ptr<Executor> m_executor;
    bool batchMode = false;

    Interpreter(unique_ptr<Parser> parser, unique_ptr<Executor> executor);

    OutputInfo extractOutputInfo(const ParsedCommand& command);
    //extracts information about where the output should be printed out

    void stripRedirectOutToken(ParsedCommand& command);
    //removes the '>>' token and the 'filename' token that is after it

    void writeOutput(const OutputInfo& outputInfo, const string& output) const;
    //prints out the output

    static Interpreter* s_instance;

public:
    Interpreter(const Interpreter&) = delete;

    static void init(unique_ptr<Parser> parser, unique_ptr<Executor> executor);
    static Interpreter& instance();

    void processLine(const string& line);
    //processes a single line
    void setBatchMode(bool f) { batchMode = f; }
    bool getBatchMode() const { return batchMode; }

};

#endif //INTERPRETER_H