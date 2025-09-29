#ifndef READER_H
#define READER_H

#define MAX_LINE_LEN 512

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Reader {
protected:
    istream& input;

public:
    explicit Reader(istream& input);
    virtual ~Reader();

    virtual string getNextLine();
    //reads a line from an input stream
    virtual bool endOfRead() const;
    //detects if EOF was detected in the input stream
    virtual bool isConsole() const = 0;
    void reset();
};


class ConsoleReader : public Reader {
public:
    ConsoleReader();
    bool isConsole() const override;
};


class FileReader : public Reader {
    ifstream file;

public:
    explicit FileReader(const string& filename);
    ~FileReader() override;

    bool endOfRead() const override;
    bool isConsole() const override;
};


#endif //READER_H
