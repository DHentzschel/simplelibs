// //////////////////////////////////////////////////////////
// sha1.h
// Copyright (c) 2014,2015 Stephan Brumme. All rights reserved.
// see http://create.stephan-brumme.com/disclaimer.html
// This file was modified and its code formatted by Daniel Hentzschel 
// in order to make it compatible to SimpleLibs libraries.
//

#pragma once

//#include "hash.h"
#include "../astring.h"
#include "../bytearray.h"

// define fixed size integer types
#ifdef _MSC_VER
// Windows
typedef unsigned __int8  uint8_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
// GCC
#include <stdint.h>
#endif


/// compute SHA1 hash
/** Usage:
    SHA1 sha1;
    std::string myHash  = sha1("Hello World");     // std::string
    std::string myHash2 = sha1("How are you", 11); // arbitrary data, 11 bytes

    // or in a streaming fashion:

    SHA1 sha1;
    while (more data available)
      sha1.add(pointer to fresh data, number of new bytes);
    std::string myHash3 = sha1.getHash();
  */
class SHA1 //: public Hash
{
public:
    /// split into 64 byte blocks (=> 512 bits), hash is 20 bytes long
    enum { BlockSize = 512 / 8, HashBytes = 20 };

    /// same as reset()
    SHA1();

    /// compute SHA1 of a memory block
    AString operator()(const ByteArray& data);
    /// compute SHA1 of a string, excluding final zero
    AString operator()(const AString& text);

    /// add arbitrary number of bytes
    void add(const ByteArray& data);

    /// return latest hash as 40 hex characters
    AString getHash();
    /// return latest hash as bytes
    void        getHash(unsigned char buffer[HashBytes]);

    /// restart
    void reset();

private:
    /// process 64 bytes
    void processBlock(const void* data);
    /// process everything left in the internal buffer
    void processBuffer();

    /// size of processed data in bytes
    uint64_t m_numBytes;
    /// valid bytes in m_buffer
    size_t   m_bufferSize;
    /// bytes not processed yet
    uint8_t  m_buffer[BlockSize];

    enum { HashValues = HashBytes / 4 };
    /// hash, stored as integers
    uint32_t m_hash[HashValues];
};
