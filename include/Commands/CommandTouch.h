#ifndef TOUCH_H
#define TOUCH_H

#include "Command.h"
#include "Writer.h"

class CommandTouch: public Command {
    //creates a file with the given name and with empty content
    //touch filename
public:
    vector<string> extractArgs(const vector<unique_ptr<Token>> &tokens) override;
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //TOUCH_H