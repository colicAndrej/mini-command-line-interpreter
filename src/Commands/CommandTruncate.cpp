#include "Commands/CommandTruncate.h"

vector<string> CommandTruncate::extractArgs(const vector<unique_ptr<Token>> &tokens) {
    vector<string> res;
    res.push_back(tokens[0]->getData());
    return res;
}

string CommandTruncate::execute(const vector<string>& args) {
    string filename = args[0];
    ifstream infile(filename);
    if (!infile.good()) {
        throw OSErrorFileDoesNotExist(filename);
    }
    infile.close();

    FileWriter file(filename);
    file.closeFile();
    return "";
}

void CommandTruncate::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {1});
    if (tokens[0]->getType() != "filename")
        throw SemanticErrorCommand("Truncate argument must not be given enclosed in quotation marks ");
}

bool CommandTruncate::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    return false;
}