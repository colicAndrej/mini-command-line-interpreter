#include "Commands/CommandDate.h"

string CommandDate::execute(const vector<string>& args) {
    time_t t = time(nullptr);
    char buffer[26];
    ctime_s(buffer, 26, &t);
    string date(buffer);
    return date.substr(4, 7) + date.substr(20, 4);
}

void CommandDate::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {0});
}

bool CommandDate::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    return false;
}