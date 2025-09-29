#ifndef TOKEN_H
#define TOKEN_H

#include "Util/Errors.h"
#include <vector>
#include <memory>

using namespace std;

class Token {
    //Abstract Class Token
    string type;
    string data;

public:
    Token(string type, string data) : type(type), data(data) {}
    ~Token() = default;

    string getType() const { return type; };
    string getData() const { return data; };
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPos) const = 0;
    //checks if the token on position 'start' of the string 'line' follows the form rules of this token type
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const = 0;
    //checks if the token on position 'i' of the vector 'tokens' follows the order rules of this token type
};

class CommandToken : public Token {
    //must be composed of lowercase letters and be at the beginning of a command
public:
    CommandToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
};

class OptToken : public Token {
    //must start with a '-' character and be composed of lowercase letters and numbers
public:
    OptToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
};

class ArgumentToken : public Token {
    //must start and end with a '"' character
    string source = "console";
public:
    ArgumentToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
    void setSource(string newSource){ source = newSource;};
    string getSource() const { return source; };
};

class FilenameToken : public Token {
    //must be composed of valid file name characters
public:
    FilenameToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
    static bool isValidFileNameChar(const char& c);
};

class RedirectInToken : public Token {
    // <
public:
    RedirectInToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
};

class RedirectOutToken : public Token {
    // >
public:
    RedirectOutToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
};

class RedirectOutAddToken : public Token {
    // >>
public:
    RedirectOutAddToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
};

class PipeToken : public Token {
    // |
public:
    PipeToken(string type, string data) : Token(type, data) {}
    virtual bool checkRules(const string& line, int start, int& end, string& type, string& data, int& errPost) const;
    virtual bool checkOrder(const vector<unique_ptr<Token>>& tokens, int i) const;
};

class TokenFactory {
public:
    unique_ptr<Token> createToken(const string& type, const string& data) const;
};



#endif //TOKEN_H
