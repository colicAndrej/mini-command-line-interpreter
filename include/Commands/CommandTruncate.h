#ifndef TRUNCATE_H
#define TRUNCATE_H

#include "Command.h"
#include "Writer.h"

class CommandTruncate: public Command {
    //deletes the contents of the file with the given name
    //truncate filename
public:
    vector<string> extractArgs(const vector<unique_ptr<Token>>& tokens) override;
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //TRUNCATE_H
