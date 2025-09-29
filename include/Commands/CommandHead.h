#ifndef HEAD_H
#define HEAD_H

#include "Command.h"

class CommandHead: public Command {
    //reads and returns first 'count' lines and ignores the rest
    //head -ncount [argument]
public:
    string execute(const vector<string>& args) override;
    void validate(const vector<unique_ptr<Token>>& tokens) override;
    bool requiresArgument(const vector<unique_ptr<Token>>& tokens) override;
};

#endif //HEAD_H
