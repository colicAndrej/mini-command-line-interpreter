#ifndef BATCH_H
#define BATCH_H

#include "Command.h"
#include "Interpreter.h"

class CommandBatch: public Command {
    //interprets any number of command lines
    //batch [argument]
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;

    vector<string> splitLines(const string& content);
};

#endif //BATCH_H
