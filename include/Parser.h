#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include <stdexcept>

struct ParsedCommand {
    string command;
    vector<unique_ptr<Token>> tokens;
};

class Parser {
    unique_ptr<Tokenizer> m_tokenizer;

    ParsedCommand makeParsedCommand(vector<unique_ptr<Token>> tokens) const;
    //converts a vector of tokens to a 'ParsedCommand' structure
    int invalidTokenIndex(const vector<unique_ptr<Token>>& tokens) const;
    //returns index of an invalid token (if every token is in a valid position then it returns -1)
    vector<ParsedCommand> separateCommands(vector<unique_ptr<Token>>& allTokens) const;
    //separates piped commands
    void handleSyntaxError(const vector<unique_ptr<Token>>& tokens, int invalidIndex) const;
    //throws a syntax error if needed

public:
    Parser(unique_ptr<Tokenizer> tokenizer);

    vector<ParsedCommand> parseLine(const string& line);
    //parses a single line (converts a string into a vector of ParsedCommand structures
};



#endif //PARSER_H
