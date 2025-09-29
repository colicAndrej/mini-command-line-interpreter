#ifndef COMMAND_H
#define COMMAND_H

#include "Token.h"
#include "Reader.h"

using namespace std;

class Command {
//Abstract Class Command
public:
     virtual ~Command() = default;

     virtual void validate(const vector<unique_ptr<Token>>& tokens) = 0;
     //checks if the correct number of arguments is provided
     virtual bool requiresArgument(const vector<unique_ptr<Token>>& tokens) = 0;
     //checks if the command requires the last argument
     virtual vector<string> extractArgs(const vector<unique_ptr<Token>>& tokens);
     //converts vector of tokens to a vector of strings that is easier for a Command class to use
     virtual string execute(const vector<string>& args) = 0;
     //executes a command and returns its output

     bool hasOpt(const vector<unique_ptr<Token>>& tokens) const;
     //checks if a vector of tokens has an 'opt' token
     void matchOpt(const vector<unique_ptr<Token>>& tokens, bool shouldExist) const;
     //matches a command's need to have an 'opt' token and its presence
     int numOfArgs(const vector<unique_ptr<Token>>& tokens) const;
     //returns a number of provided 'argument' tokens
     void matchArgs(const vector<unique_ptr<Token>>& tokens, const vector<int>& validNums) const;
     //matches a command's required number of 'argument' tokens and its actual number of provided 'argument' tokens
     static string readArgFromFile(const string& filename);
     //reads an argument from a file
};

#endif //COMMAND_H