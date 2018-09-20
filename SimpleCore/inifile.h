#ifndef INIFILE_H
#define INIFILE_H

#include "astring.h"

class IniFile {
public:
    IniFile() = default;

    explicit IniFile(const AString& filepath);

    ~IniFile() = default;

    void setFilepath(const AString& filepath);

    void beginGroup(const AString& group);

    void endGroup();

    uint getGroupCount();

    uint getKeyCount();

    AString value(const AString& key) const;

    void setValue(const AString& key, const AString& value) const;

private:
    AString filepath_;

    AString group_;

    AVector<AString> fileContent_;

    uint groupCount_;

    uint keyCount_;

    void calculateGroupCount();

    void calculateKeyCount();
};

#endif // INIFILE_H
