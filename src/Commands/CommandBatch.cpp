#include "Commands/CommandBatch.h"

string CommandBatch::execute(const vector<string>& args) {
    vector<string> lines = splitLines(args[0]);

    string output;
    Interpreter::instance().setBatchMode(true);
    for (int i = 0; i < lines.size(); i++) {
        try {
            Interpreter::instance().processLine(lines[i]);
        } catch (const exception& e) {
            output += ("Error on line " + to_string(i + 1) + ": " + e.what() + '\n');
        }
    }
    Interpreter::instance().setBatchMode(false);

    if (!output.empty() && output.back() == '\n')
        output.pop_back();
    return output;
}

void CommandBatch::validate(const vector<unique_ptr<Token>> &tokens) {
    matchOpt(tokens, false);
    matchArgs(tokens, {1});
}

bool CommandBatch::requiresArgument(const vector<unique_ptr<Token>>& tokens) {
    int n = numOfArgs(tokens);
    if (!hasOpt(tokens) && n == 0)
        return true;
    if (hasOpt(tokens))
        return false;

    return false;
}

vector<string> CommandBatch::splitLines(const string& content) {
    vector<string> lines;
    string line;
    for (int i = 0; i < content.length(); i++) {
        if (content[i] == '\n' && !line.empty()) {
            lines.push_back(line);
            line.clear();
        }
        else
            line += content[i];
    }
    if (!line.empty())
        lines.push_back(line);
    return lines;
}