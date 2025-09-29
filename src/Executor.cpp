#include "Executor.h"
#include "Interpreter.h"

Executor::Executor(unique_ptr<CommandFactory> commandFactory)
    : m_commandFactory(move(commandFactory)) {
    m_reader = new ConsoleReader();
}

Executor::~Executor() {
    delete m_reader;
}

string Executor::executeCommands(vector<ParsedCommand>& commands) {
    if (commands.empty())
        return "";
    ParsedCommand& firstCommand = commands[0];
    openRedirectInToken(firstCommand);
    if (requiresArgument(firstCommand) && !Interpreter::instance().getBatchMode()) {
        string missingArg = "";
        while (true) {
            string line = m_reader->getNextLine();
            if (m_reader->endOfRead()) {
                m_reader->reset();
                break;
            }
            missingArg += line + '\n';
        }
        if (!missingArg.empty() && missingArg.back() == '\n')
            missingArg.pop_back();

        insertToken(firstCommand.tokens, missingArg);
    }

    string output = executeSingleCommand(firstCommand);
    output = executeRestOfPipedCommands(commands, output);
    return output;
}

string Executor::executeSingleCommand(const ParsedCommand &parsedCommand) {
    if (parsedCommand.command.empty())
        throw NoCommandError();
    unique_ptr<Command> command;
    command = m_commandFactory->createCommand(parsedCommand.command);
    command->validate(parsedCommand.tokens);
    vector<string> args = command->extractArgs(parsedCommand.tokens);
    return command->execute(args);
}

string Executor::executeRestOfPipedCommands(vector<ParsedCommand>& parsedCommands, const string& firstOutput) {
    string output = firstOutput;
    for (int i = 1;i < parsedCommands.size(); i++) {
        insertToken(parsedCommands[i].tokens, output);
        output = executeSingleCommand(parsedCommands[i]);
    }
    return output;
}

void Executor::insertToken(vector<unique_ptr<Token>>& tokens, const string& data) {
    unique_ptr<Token> token = make_unique<ArgumentToken>("argument", data);
    for (int i = 0; i<tokens.size(); i++) {
        if (tokens[i]->getType() != "opt") {
            tokens.insert(tokens.begin() + i, move(token));
            return;
        }
    }
    tokens.push_back(move(token));
}

void Executor::openRedirectInToken(ParsedCommand& parsedCommand) {
    vector<unique_ptr<Token>>& tokens = parsedCommand.tokens;

    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i]->getType() == "redirect_in") {
            string data = Command::readArgFromFile(tokens[i+1]->getData());
            tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);
            insertToken(tokens, data);
            int pos = 0;
            if (tokens[0]->getType() == "opt")
                pos = 1;
            if (ArgumentToken* arg = dynamic_cast<ArgumentToken*>(tokens[pos].get()))
                arg->setSource("redirect");
            return;
        }
    }
}

bool Executor::requiresArgument(const ParsedCommand& parsedCommand) const {
    if (parsedCommand.command.empty())
        throw NoCommandError();

    unique_ptr<Command> command = m_commandFactory->createCommand(parsedCommand.command);
    return command->requiresArgument(parsedCommand.tokens);
}