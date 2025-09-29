#include "Token.h"


bool CommandToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    int ind = start;
    if (ind != 0) {
        ind--;
        while (ind != 0 && isspace(line[ind]))
            ind--;
        if (ind != 0 && line[ind] != '|')
            return false;
    }
    string temp = "";
    ind  = start;
    while (ind < line.length() && !isspace(line[ind]) && islower(line[ind])) {
        temp += line[ind++];
    }
    if (temp.empty()) return false;
    if (ind < line.length() && !isspace(line[ind])) {
        errPos = max(errPos, ind);
        return false;
    }

    type = "command";
    data = temp;
    end = ind;
    return true;
}

bool CommandToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i == 0)
        return true;
    if (tokens[i-1]->getType() != "pipe")
        return false;
    return true;
}

bool OptToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    if (line[start] == '-') {
        string temp = "-";
        int ind = start + 1;
        while (ind < line.length() && !isspace(line[ind])) {
            if (!(islower(line[ind]) || isdigit(line[ind]))) {
                errPos = max(errPos, ind);
                return false;
            }
            temp += line[ind++];
        }

        type = "opt";
        data = temp;
        end = ind;
        return true;
    }
    return false;
}

bool OptToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i == 0)
        return false;
    if (tokens[i-1]->getType() != "command")
        return false;
    return true;
}

bool ArgumentToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    if (line[start] == '"') {
        string temp = "";
        int ind = start + 1;
        while (ind < line.length() && line[ind] != '"')
            temp += line[ind++];
        if (ind == line.length()) {
            errPos = max(errPos, start);
            return false;
        }

        type = "argument";
        data = temp;
        end = ind+1;
        return true;
    }
    return false;
}

bool ArgumentToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i == 0)
        return false;
    string prevType = tokens[i-1]->getType();
    if (prevType != "command" &&
        prevType != "opt" &&
        prevType != "argument" &&
        prevType != "filename")
        return false;
    return true;
}

bool FilenameToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    string temp = "";
    int ind = start;
    while (ind<line.length() && !isspace(line[ind])) {
        if (!isValidFileNameChar(line[ind])) {
            errPos = max(errPos, ind);
            return false;
        }
        temp += line[ind++];
    }

    type = "filename";
    data = temp;
    end = ind;
    return true;
}

bool FilenameToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i == 0)
        return false;
    if (tokens[i-1]->getType() == "pipe")
        return false;
    return true;
}

bool FilenameToken::isValidFileNameChar(const char &c) {
    return c != '?' && c != '*' && c != '"' && c != '<' && c != '>' && c != '|';
}

bool RedirectInToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    if (line[start] == '<') {
        type = "redirect_in";
        data = "<";
        end = start + 1;
        return true;
    }
    errPos = max(errPos, start);
    return false;
}

bool RedirectInToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i == 0)
        return false;
    string prevType = tokens[i-1]->getType();
    if (prevType != "command" &&
        prevType != "opt" &&
        prevType != "argument" &&
        prevType != "filename")
        return false;
    int pipePos = -1;
    for (int j = 0; j < tokens.size(); j++) {
        if (tokens[j]->getType() == "pipe") {
            pipePos = j;
            break;
        }
    }
    if (pipePos != -1 && i == pipePos - 2)
        return true;
    if (i != tokens.size() - 2 && i != tokens.size() - 4)
        return false;
    return true;
}

bool RedirectOutToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    if (line[start] == '>' && !(start + 1 < line.size() && line[start + 1] == '>')) {
        type = "redirect_out";
        data = ">";
        end = start + 1;
        return true;
    }
    errPos = max(errPos, start);
    return false;
}

bool RedirectOutToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i != tokens.size() - 2)
        return false;
    if (tokens[i+1]->getType() != "filename")
        return false;
    return true;
}

bool RedirectOutAddToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    if (line[start] == '>' && start + 1 < line.size() && line[start + 1] == '>') {
        type = "redirect_out_add";
        data = ">>";
        end = start + 2;
        return true;
    }
    errPos = max(errPos, start);
    return false;
}

bool RedirectOutAddToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i != tokens.size() - 2)
        return false;
    if (tokens[i+1]->getType() != "filename")
        return false;
    return true;
}

bool PipeToken::checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const {
    if (line[start] == '|') {
        type = "pipe";
        data = "|";
        end = start + 1;
        return true;
    }
    errPos = max(errPos, start);
    return false;
}

bool PipeToken::checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const {
    if (i == 0 || i == tokens.size() - 1)
        return false;
    if (tokens[i+1]->getType() != "command")
        return false;
    if (tokens[i-1]->getType() != "command" &&
        tokens[i-1]->getType() != "opt" &&
        tokens[i-1]->getType() != "argument" &&
        tokens[i-1]->getType() != "filename")
        return false;
    return true;
}

unique_ptr<Token> TokenFactory::createToken(const string& type, const string& data) const {
    if (type == "command")
        return make_unique<CommandToken>(type, data);
    if (type == "opt")
        return make_unique<OptToken>(type, data);
    if (type == "argument")
        return make_unique<ArgumentToken>(type, data);
    if (type == "filename")
        return make_unique<FilenameToken>(type, data);
    if (type == "redirect_in")
        return make_unique<RedirectInToken>(type, data);
    if (type == "redirect_out")
        return make_unique<RedirectOutToken>(type, data);
    if (type == "redirect_out_add")
        return make_unique<RedirectOutAddToken>(type, data);
    if (type == "pipe")
        return make_unique<PipeToken>(type, data);
    return nullptr;
}