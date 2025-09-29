#ifndef TIMECMD_H
#define TIMECMD_H

#include "Command.h"
#include <ctime>

class Time: public Command {
    //returns the current time
    //time
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //TIMECMD_H
