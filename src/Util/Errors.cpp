#include "Util/Errors.h"

#include "Commands/Command.h"

LexicalError::LexicalError(const string &message)
    :runtime_error("Lexical Error: " + message){}


CommandError::CommandError(const string &message)
    :runtime_error("Command Error: " + message){}

NoCommandError::NoCommandError()
    :CommandError("No command provided"){}

UknownCommandError::UknownCommandError(const string &command)
    :CommandError("Unknown command '" + command + "'") {}


SyntaxError::SyntaxError(const string &message)
    :runtime_error("Syntax Error: " + message){}


SemanticError::SemanticError(const string &message)
    :runtime_error("Semantic Error: " + message){}

SemanticErrorCommand::SemanticErrorCommand(const string &command)
    :SemanticError("Invalid command: " + command){}

SemanticErrorMustBeFilename::SemanticErrorMustBeFilename(const string &command)
    :SemanticError(command + " argument must be given as a file name"){}


InvalidOptionError::InvalidOptionError(const string &opt)
    :runtime_error("Invalid option provided '" + opt + "'"){}


OSError::OSError(const string &message)
    :runtime_error("OSError: " + message){}

OSErrorCannotOpenFile::OSErrorCannotOpenFile(const string &filename)
    :OSError("Cannot open file '" + filename + "'"){}

OSErrorFileAlreadyExists::OSErrorFileAlreadyExists(const string &filename)
    :OSError("File already exists '" + filename + "'"){}

OSErrorFileDoesNotExist::OSErrorFileDoesNotExist(const string &filename)
    :OSError("File doesn't exist '" + filename + "'"){}