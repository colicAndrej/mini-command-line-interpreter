#include "Tokenizer.h"

void Tokenizer::handleLexicalError(const string &line, int errPos) {
    string errLine(line.length(), ' ');
    errLine[errPos] = '^';
    throw LexicalError("Unexpected character\n" + line + "\n" + errLine);
}

Tokenizer::Tokenizer() {
    rules.push_back(std::make_unique<CommandToken>("command", ""));
    rules.push_back(std::make_unique<OptToken>("opt", ""));
    rules.push_back(std::make_unique<ArgumentToken>("argument", ""));
    rules.push_back(std::make_unique<FilenameToken>("filename", ""));
    rules.push_back(std::make_unique<RedirectInToken>("redirect_in", ""));
    rules.push_back(std::make_unique<RedirectOutToken>("redirect_out", ""));
    rules.push_back(std::make_unique<RedirectOutAddToken>("redirect_out_add", ""));
    rules.push_back(std::make_unique<PipeToken>("pipe", ""));

    tokenFactory = std::make_unique<TokenFactory>();
}

vector<unique_ptr<Token>> Tokenizer::tokenize(const string &line) {
    vector<unique_ptr<Token>> res;
    int i=0;
    while (i < line.length()) {
        if (isspace(line[i])) {
            i++;
            continue;
        }
        bool found = false;
        int firstErrPos = -1;
        for (int j = 0; j < rules.size(); j++) {
            string type, data;
            int end = i;
            int errPos = -1;
            if (rules[j]->checkRules(line, i, end, type, data, errPos)) {
                found = true;
                res.push_back(tokenFactory->createToken(type, data));
                i = end;
                break;
            }
            if (firstErrPos == -1)
                firstErrPos = errPos;
        }
        if (!found) {
            if (firstErrPos == -1)
                firstErrPos = i;
            handleLexicalError(line, firstErrPos);
        }
    }
    return res;
}