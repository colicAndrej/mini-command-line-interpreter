#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Parser.h"
#include "Reader.h"
#include "CommandFactory.h"

class CommandFactory;
class Interpreter;

class Executor {
    Reader* m_reader;
    unique_ptr<CommandFactory> m_commandFactory;

    void insertToken(vector<unique_ptr<Token>>& tokens, const string& data);
    //inserts token with data 'data' as a first token in the vector 'tokens'
    void openRedirectInToken(ParsedCommand& parsedCommand);
    //reads content from 'redirect in' file
    bool requiresArgument(const ParsedCommand& parsedCommand) const;
    //checks if the program should enter multiline input for getting the last argument

    string executeSingleCommand(const ParsedCommand& parsedCommand);
    //executes a command
    string executeRestOfPipedCommands(vector<ParsedCommand>& parsedCommands, const string& firstOutput);
    //executes piped commands after the first command

public:
    Executor(unique_ptr<CommandFactory> commandFactory);
   ~Executor();

    string executeCommands(vector<ParsedCommand>& commands);
    //executes the whole command line
};


#endif //EXECUTOR_H
