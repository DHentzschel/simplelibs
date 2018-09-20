#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

#define DELETE_PTR(x)                                                          \
    delete (x);                                                                  \
    (x) = nullptr;
#define DELETE_ARR(x)                                                          \
    delete[] (x);                                                                \
    (x) = nullptr;

#define ZEROMEMORY(x) memset(x, 0, sizeof (x))

#define IS_NULL(x) x == nullptr
#define NOT_NULL(x) x != nullptr

#define TO_STRING(x) AString::toString(x)
#define TO_STRING_BOOL(x) AString::toString(x, true)  

#define STATIC_CAST(type, x) (static_cast<type>(x))
#define REINTERPRET_CAST(type, x) (reinterpret_cast<type>(x))
#define DYNAMIC_CAST(type, x) (dynamic_cast<type>(x))
#define CONST_CAST(type, x) (const_cast<type>(x))

#define SHARED_PTR(x) std::shared_ptr<x>
#define MAKE_SHARED(type, x) std::make_shared<type>(x)

#define UNIQUE_PTR(x) std::unique_ptr<x>
#define MAKE_UNIQUE(type, x) std::make_unique<type>(x)

#define WEAK_PTR(x) std::weak_ptr<x>

#define CAST_VOID_PTR(x) (static_cast<void*>(x))

#define CAST_BOOL(x) static_cast<bool>(x)
#define CAST_BOOL_PTR(x) (static_cast<bool*>(x))

#define CAST_CHAR_PTR(x) (static_cast<char*>(x))

#define CAST_CHAR(x) static_cast<char>(x)
#define CAST_CHAR_PTR(x) (static_cast<char*>(x))

#define CAST_BYTE(x) static_cast<byte>(x)
#define CAST_BYTE_PTR(x) (static_cast<byte*>(x))

#define CAST_SHORT(x) static_cast<short>(x)
#define CAST_SHORT_PTR(x) (static_cast<short*>(x))

#define CAST_USHORT(x) static_cast<ushort>(x)
#define CAST_USHORT_PTR(x) (static_cast<ushort*>(x))

#define CAST_INT(x) static_cast<int>(x)
#define CAST_INT_PTR(x) (static_cast<int*>(x))

#define CAST_UINT(x) static_cast<uint>(x)
#define CAST_UINT_PTR(x) (static_cast<uint*>(x))

#define CAST_LONG(x) static_cast<long>(x)
#define CAST_LONG_PTR(x) (static_cast<long*>(x))

#define CAST_ULONG(x) static_cast<ulong>(x)
#define CAST_ULONG_PTR(x) (static_cast<ulong*>(x))

#define CAST_LONGLONG(x) static_cast<int64>(x)
#define CAST_LONGLONG_PTR(x) (static_cast<int64*>(x))

#define CAST_ULONGLONG(x) static_cast<uint64>(x)
#define CAST_ULONGLONG_PTR(x) (static_cast<uint64*>(x))

#define CAST_FLOAT(x) static_cast<float>(x)
#define CAST_FLOAT_PTR(x) (static_cast<float*>(x))

#define CAST_DOUBLE(x) static_cast<double>(x)
#define CAST_DOUBLE_PTR(x) (static_cast<double*>(x))

#endif   // FUNCTIONS_H
