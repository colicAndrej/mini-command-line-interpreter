#include "Interpreter.h"

Interpreter* Interpreter::s_instance = nullptr;

Interpreter::Interpreter(unique_ptr<Parser> parser, unique_ptr<Executor> executor)
    : m_parser(move(parser)), m_executor(move(executor)) {}

void Interpreter::init(unique_ptr<Parser> parser, unique_ptr<Executor> executor) {
    s_instance = new Interpreter(move(parser), move(executor));
}

Interpreter& Interpreter::instance() {
    return *s_instance;
}

void Interpreter::processLine(const string &line) {
        vector<ParsedCommand> parsedCommands = m_parser->parseLine(line);
        OutputInfo outputInfo = extractOutputInfo(parsedCommands.back());
        stripRedirectOutToken(parsedCommands.back());
        string output = m_executor->executeCommands(parsedCommands);
        writeOutput(outputInfo, output);
}

OutputInfo Interpreter::extractOutputInfo(const ParsedCommand& command) {
    OutputInfo outputInfo;
    const vector<unique_ptr<Token>>& tokens = command.tokens;
    int n = tokens.size();
    if (n >= 2) {
        if (tokens[n-2]->getType() == "redirect_out") {
            outputInfo.redirectOut = true;
            outputInfo.filename = tokens.back()->getData();
        }
        else if (tokens[n-2]->getType() == "redirect_out_add") {
            outputInfo.redirectOut = true;
            outputInfo.add = true;
            outputInfo.filename = tokens.back()->getData();
        }
    }
    return outputInfo;
}

void Interpreter::stripRedirectOutToken(ParsedCommand& command) {
    vector<unique_ptr<Token>>& tokens = command.tokens;
    int n = tokens.size();
    if (n>=2) {
        if (tokens[n-2]->getType() == "redirect_out" ||
            tokens[n-2]->getType() == "redirect_out_add") {
            tokens.pop_back();
            tokens.pop_back();
            }
    }
}

void Interpreter::writeOutput(const OutputInfo& outputInfo, const string& output) const {
    if (outputInfo.redirectOut) {
        FileWriter *writer = new FileWriter;
        writer->openFile(outputInfo.filename, outputInfo.add);
        writer->write(output);
        delete writer;
    }
    else {
        cout<<output;
        if (!output.empty())
            cout<<"\n";
    }
}
