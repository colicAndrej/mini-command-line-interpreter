#include "Commands/Command.h"

vector<string> Command::extractArgs(const vector<unique_ptr<Token>> &tokens) {
    vector<string> res;
    for (int i = 0; i<tokens.size(); i++) {
        if (tokens[i]->getType() == "filename") {
            string arg = readArgFromFile(tokens[i]->getData());
            res.push_back(arg);
        }
        else
            res.push_back(tokens[i]->getData());
    }

    return res;
}

bool Command::hasOpt(const vector<unique_ptr<Token>>& tokens) const {
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i]->getType() == "opt")
            return true;
    }
    return false;
}

void Command::matchOpt(const vector<unique_ptr<Token>> &tokens, bool shouldExist) const {
    if (hasOpt(tokens) != shouldExist) {
        string msg;
        if (shouldExist)
            throw SemanticErrorCommand("No option provided");
        throw SemanticErrorCommand("Got an option but expected none");

    }
}

int Command::numOfArgs(const vector<unique_ptr<Token>>& tokens) const {
    int count = 0;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i]->getType() == "argument" || tokens[i]->getType() == "filename")
            count++;
    }
    return count;
}

void Command::matchArgs(const vector<unique_ptr<Token>> &tokens, const vector<int> &validNums) const {
    int n = numOfArgs(tokens);
    bool valid = false;
    for (int i = 0; i < validNums.size(); i++) {
        if (n == validNums[i])
            valid = true;
    }
    if (!valid) {
        string msg = "Invalid number of arguments\nExpected " + to_string(validNums[0]);
        if (validNums.size() > 1)
            msg += "-" + to_string(validNums[validNums.size()-1]);
        if (validNums.size() == 1 && validNums[0] == 1)
            msg += " argument";
        else
            msg += " arguments";
        msg += " but got " + to_string(n);
        throw SemanticErrorCommand(msg);
    }
}

string Command::readArgFromFile(const string& filename){
    unique_ptr<FileReader> fileReader = make_unique<FileReader>(filename);
    string arg;
    while (!fileReader->endOfRead()) {
        arg += fileReader->getNextLine();
        if (!fileReader->endOfRead())
            arg += '\n';
    }
    return arg;
}
