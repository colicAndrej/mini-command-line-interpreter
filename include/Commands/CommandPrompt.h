#ifndef COMMANDPROMPT_H
#define COMMANDPROMPT_H

#include "Command.h"

extern string prompt;

class Prompt: public Command {
    //sets a signal for the interpreter to be ready to load a new command line to 'argument'
    //prompt argument
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //COMMANDPROMPT_H
