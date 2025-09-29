#ifndef WRITER_H
#define WRITER_H

#include <fstream>

using namespace std;

class Writer {
public:
    virtual ~Writer() = default;

    virtual void write(const string& data) = 0;
};

class FileWriter : public Writer {
    ofstream file;
    bool isOpen = false;
public:
    FileWriter();
    FileWriter(const string& filename, bool add = false);
    virtual ~FileWriter();

    void openFile(const string &filename, bool add = false);
    //opens file
    void closeFile();
    //closes file
    bool opened() const;
    virtual void write(const string& data);
    //insert 'data' in a file
};

#endif //WRITER_H