#ifndef WC_H
#define WC_H

#include "Command.h"

class CommandWc: public Command {
    //counts the number of words if opt=w or counts the number of characters if opt=c in 'argument'
    //wc -opt [argument]
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //WC_H
