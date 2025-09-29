#ifndef TR_H
#define TR_H

#include "Command.h"

class CommandTr: public Command {
    //replaces all the 'what' appearances in 'argument' with 'with'
    //tr [argument] what [with]
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //TR_H
