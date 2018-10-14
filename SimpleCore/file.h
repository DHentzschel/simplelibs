#ifndef FILE_H
#define FILE_H

#include <fstream>

#include "astring.h"
#include "avector.h"
#include "openmode.h"

using namespace OpenMode;

class File {
public:
    File();

    explicit File(const AString& filename);

    ~File();

    bool create(bool recursively = true) const;

    static bool create(const AString& filepath, bool recursively = true);

    bool erase() const;

    static bool erase(const AString& filepath);

    bool exists() const;

    static bool exists(const AString& filepath);

    AString getDirectory() const;

    AString getFilename() const;

    AString getFilepath() const;

    void setFilePath(const AString& filepath);

    bool isOpen() const;

    bool open(int openMode = NotOpen);

    void close();

    std::fstream& operator<<(const AString& string);

    void append(const AString& string);

    AString readAllText();

    void writeAllText(const AString& text);

    ByteArray readAllBytes();

    void writeAllBytes(const AVector<char>& bytes);

    AString readLine();

    bool atEnd() const;

private:
    AString filepath_;

    std::fstream fstream_;

    int openMode_;

    bool printFileOpen() const;

    bool printFlagReadOnly() const;

    bool printFlagWriteOnly() const;
};

#endif   // FILE_H
