#ifndef ERROR_H
#define ERROR_H

#include <stdexcept>
#include <string>

using namespace std;

//Lexical errors
class LexicalError: public runtime_error {
public:
    LexicalError(const string& message);
};

//Command errors
class CommandError: public runtime_error {
public:
    explicit CommandError(const string& message);
};

class NoCommandError: public CommandError {
public:
    NoCommandError();
};

class UknownCommandError: public CommandError {
public:
    explicit UknownCommandError(const string& command);
};

//Syntax errors
class SyntaxError: public runtime_error {
public:
    SyntaxError(const string& message);
};

//Semantic errors
class SemanticError: public runtime_error {
public:
    explicit SemanticError(const string& message);
};

class SemanticErrorCommand: public SemanticError {
public:
    SemanticErrorCommand(const string& command);
};

class SemanticErrorMustBeFilename: public SemanticError {
public:
    SemanticErrorMustBeFilename(const string& command);
};

//Option errors
class InvalidOptionError: public runtime_error {
public:
    InvalidOptionError(const string& opt);
};

//OS errors
class OSError: public runtime_error {
public:
    OSError(const string& message);
};

class OSErrorCannotOpenFile: public OSError {
public:
    OSErrorCannotOpenFile(const string& filename);
};

class OSErrorFileAlreadyExists: public OSError {
public:
    OSErrorFileAlreadyExists(const string& filename);
};

class OSErrorFileDoesNotExist: public OSError {
public:
    OSErrorFileDoesNotExist(const string& filename);
};

#endif //ERROR_H
