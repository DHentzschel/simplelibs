#ifndef CHAR_H
#define CHAR_H

/**
 * This class is used as auxiliary class for characters.
 *
 * @author Daniel Hentzschel on 12.05.2019.
 */
class Char {
public:
    explicit Char(const char c) : c_(c)
    {}

    bool isWhitespace() const
    {
        return c_ == '\t' || c_ == '\r' || c_ == '\n' || c_ == ' ' || c_ == '\f' || c_ == '\v';
    }

    char toLower() const
    {
        return c_ | 0x20;
    }

    char toUpper() const
    {
        return c_ & ~0x20;
    }

private:
    char c_;
};

#endif   // CHAR_H
