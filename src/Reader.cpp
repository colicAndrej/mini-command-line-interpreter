#include "Reader.h"

#include "Util/Errors.h"

Reader::Reader(istream& input): input(input){}

Reader::~Reader() {}

string Reader::getNextLine() {
    string line = "";
    char c;
    int count = 0;
    while (input.get(c)) {
        if (c == '\n') break;
        if (count++ < MAX_LINE_LEN) {
            if (c < 32) {
                line += '^';
                if (count++ < MAX_LINE_LEN)
                    line += ('A' + c - 1);
            }
            else
                line += c;
        }
    }
    return line;
}

bool Reader::endOfRead() const{
    return input.eof();
}


void Reader::reset() {
    input.clear();
}

ConsoleReader::ConsoleReader(): Reader(cin) {}

bool ConsoleReader::isConsole() const { return true;}


FileReader::FileReader(const string& filename): file(filename), Reader(file) {
    if (!file.is_open())
        throw OSErrorCannotOpenFile(filename);
}

FileReader::~FileReader() {
    file.close();
}

bool FileReader::endOfRead() const {
    return file.eof();
}

bool FileReader::isConsole() const {return false;}
