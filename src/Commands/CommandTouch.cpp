#include "Commands/CommandTouch.h"

vector<string> CommandTouch::extractArgs(const vector<unique_ptr<Token>> &tokens) {
    vector<string> res;
    res.push_back(tokens[0]->getData());
    return res;
}

string CommandTouch::execute(const vector<string>& args) {
    string filename = args[0];
    ifstream infile(filename);
    if (infile.good()) {
        throw OSErrorFileAlreadyExists(filename);
    }
    infile.close();

    FileWriter file(filename);
    file.closeFile();
    return "";
}

void CommandTouch::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {1});
    if (tokens[0]->getType() != "filename")
        throw SemanticErrorMustBeFilename("Touch");
}

bool CommandTouch::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    return false;
}