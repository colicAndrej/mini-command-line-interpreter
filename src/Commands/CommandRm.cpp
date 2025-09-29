#include "Commands/CommandRm.h"

vector<string> CommandRm::extractArgs(const vector<unique_ptr<Token>> &tokens) {
    vector<string> res;
    res.push_back(tokens[0]->getData());
    return res;
}

string CommandRm::execute(const vector<string>& args) {
    string filename = args[0];
    ifstream infile(filename);
    if (!infile.good()) {
        throw OSErrorFileDoesNotExist(filename);
    }
    infile.close();

    remove(filename.c_str());
    return "";
}

void CommandRm::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {1});
    if (tokens[0]->getType() != "filename")
        throw SemanticErrorMustBeFilename("Rm");
}

bool CommandRm::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    return false;
}