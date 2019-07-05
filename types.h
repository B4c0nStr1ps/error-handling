#pragma once

/*
Exception to coding style (Name of types should start with capital letter).
*/

typedef signed char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned u16;
typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned char byte;

constexpr u64 k_MiB = 1048576u;
constexpr u64 k_KiB = 1024;

template <u64 Alignment, u64 Size>
struct Aligned_byte_buffer {
  alignas(Alignment) byte buffer[Size];
};

template <typename T>
struct Aligned_type_storage : Aligned_byte_buffer<alignof(T), sizeof(T)> {
};

#define FORCEINLINE __forceinline