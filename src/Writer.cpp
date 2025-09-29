#include "Writer.h"

#include "Util/Errors.h"

FileWriter::~FileWriter() {
    closeFile();
}

FileWriter::FileWriter() = default;

FileWriter::FileWriter(const string &fileName, bool add) {
    openFile(fileName, add);
}

void FileWriter::openFile(const string &filename, bool add) {
    closeFile();

    if (!add)
        file.open(filename);
    else
        file.open(filename, ios::app);
    if (!file.is_open())
        throw OSErrorCannotOpenFile(filename);

    isOpen = true;
}


void FileWriter::closeFile() {
    if (isOpen) {
        file.close();
        isOpen = false;
    }
}

bool FileWriter::opened() const {
    return isOpen;
}

void FileWriter::write(const string &data) {
    if (isOpen)
        file << data;
}