#ifndef ECHO_H
#define ECHO_H

#include "Command.h"

class CommandEcho: public Command {
    //returns characters without any modification
    //echo [argument]
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //ECHO_H