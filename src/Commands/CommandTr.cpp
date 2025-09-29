#include "Commands/CommandTr.h"

string CommandTr::execute(const vector<string>& args) {
    string text = args[0];
    string what = args[1], with = "";
    if(what.empty())
        throw SemanticErrorCommand("Argument 'what' cannot be empty");
    if (args.size() > 2) {
        with = args[2];
    }
    string res = "";
    string curr = "";
    int i = 0, j = 0;
    while(i < text.size()){
        if(text[i] == what[j]){
            curr += text[i++];
            j++;
            if (j == what.size()){
                res += with;
                j = 0;
                curr.clear();
            }
        }
        else{
            res += curr;
            curr.clear();
            res += text[i++];
            j = 0;
        }
    }
    res += curr;

    return res;
}

void CommandTr::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {2, 3});
}

bool CommandTr::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    int n = numOfArgs(tokens);
    if (!hasOpt(tokens) && (n == 1 || n == 2)) {
        ArgumentToken* argToken = dynamic_cast<ArgumentToken*>(tokens[0].get());
        if (argToken && argToken->getSource() == "redirect")
            return false;
        return true;
    }
    return false;
}