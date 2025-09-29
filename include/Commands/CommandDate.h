#ifndef DATE_H
#define DATE_H

#include "Command.h"
#include <ctime>

class CommandDate: public Command {
    //returns the current date
    //date
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //DATE_H
