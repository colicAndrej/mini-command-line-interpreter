#ifndef RM_H
#define RM_H

#include "Command.h"
#include "Writer.h"

class CommandRm: public Command {
    //deletes the file with the given name
    //rm filename
public:
    vector<string> extractArgs(const vector<unique_ptr<Token>>& tokens) override;
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //RM_H
