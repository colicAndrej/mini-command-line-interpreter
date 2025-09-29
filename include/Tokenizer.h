#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"

class Tokenizer {
    vector<unique_ptr<Token>> rules;
    unique_ptr<TokenFactory> tokenFactory;

    void handleLexicalError(const string& line, int errPos);
    //throws a lexical error if needed

public:
    Tokenizer();
    ~Tokenizer() = default;

    vector<unique_ptr<Token>> tokenize(const string &line);
    //tokenizez a single line (converts a string into a vector of tokens)
};

#endif //TOKENIZER_H