#include "Parser.h"

Parser::Parser(unique_ptr<Tokenizer> tokenizer): m_tokenizer(move(tokenizer)) {}

vector<ParsedCommand> Parser::parseLine(const string &line) {
        vector<unique_ptr<Token>> tokens;
        tokens = m_tokenizer->tokenize(line);
        handleSyntaxError(tokens, invalidTokenIndex(tokens));
        vector<ParsedCommand> separatedCommands = separateCommands(tokens);
        return separatedCommands;
}

vector<ParsedCommand> Parser::separateCommands(vector<unique_ptr<Token>>& allTokens) const {
    vector<ParsedCommand> separatedCommands;
    vector<unique_ptr<Token>> currentTokens;
    for (int i = 0; i < allTokens.size(); i++) {
        if (allTokens[i]->getType() != "pipe")
            currentTokens.push_back(move(allTokens[i]));
        else {
            separatedCommands.push_back(makeParsedCommand(move(currentTokens)));
            currentTokens.clear();
        }
    }
    if (!currentTokens.empty())
        separatedCommands.push_back(makeParsedCommand(move(currentTokens)));
    return separatedCommands;
}

void Parser::handleSyntaxError(const vector<unique_ptr<Token>> &tokens, int invalidIndex) const {
    if (invalidIndex == -1)
        return;
    string errorMsg = "Invalid token order";
    throw SyntaxError(errorMsg);
}

ParsedCommand Parser::makeParsedCommand(vector<unique_ptr<Token>> tokens) const {
    ParsedCommand parsedCommand;
    parsedCommand.command = tokens[0]->getData();
    tokens.erase(tokens.begin());
    parsedCommand.tokens = move(tokens);
    return parsedCommand;
}

int Parser::invalidTokenIndex(const vector<unique_ptr<Token>>& tokens) const {
    for (int i = 0; i < tokens.size(); i++) {
        if (!tokens[i]->checkOrder(tokens, i))
            return i;
    }
    return -1;
}