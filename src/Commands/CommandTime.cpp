#include "Commands/CommandTime.h"

string Time::execute(const vector<string>& args) {
    time_t t = time(nullptr);
    char buffer[26];
    ctime_s(buffer, 26, &t);
    string date(buffer);
    return date.substr(11, 8);
}

void Time::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {0});
}

bool Time::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    return false;
}