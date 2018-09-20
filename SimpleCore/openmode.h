#ifndef FILEIO_H
#define FILEIO_H

namespace OpenMode {
    static const int NotOpen = 0x0;
    static const int ReadOnly = 0x1;
    static const int WriteOnly = 0x2;
    static const int ReadWrite = ReadOnly | WriteOnly;
    static const int AtTheEnd = 0x4;
    static const int Append = 0x8;
    static const int Truncate = 0x10;
    static const int Binary = 0x20;
    static const int NewOnly = 0x40;
    static const int ExistingOnly = 0x80;
};   // namespace OpenMode

#endif   // FILEIO_H
