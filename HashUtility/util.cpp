//
//  util.cpp
//  HashUtility
//
//  Created by Achoual Othmane on 02/10/2018.
//  Copyright © 2018 Achoual Othmane. All rights reserved.
//

#include "util.h"
#include <cstdlib>

unsigned int left_rotate(unsigned int x, unsigned int c)
{
    return (x << c) | (x >> (32 - c));
}

unsigned int right_rotate(unsigned int x, unsigned int c)
{
    return (x >> c) | (x << (32 - c));
}

unsigned int as_big_endian(unsigned int le)
{
    char r[4];
    for (int i = 1; i <= 4; ++i)
    {
        r[4 - i] = le & 0xff;
        le >>= 8;
    }
    return *((unsigned int *)r);
}

unsigned int get_padded_length_in_bits(unsigned int plain_length)
{
    unsigned int padded_length_in_bits = plain_length * 8;
    padded_length_in_bits += 1;
    unsigned int rem = padded_length_in_bits % 512;
    padded_length_in_bits += (rem <= 448) ? (448 - rem) : (448 + (512 - rem));
    padded_length_in_bits += 64;
    
    return padded_length_in_bits;
}

void pad(const char *plain, char *padded, unsigned int offset, size_t num_zero_bytes)
{
    memcpy(padded, plain, sizeof(char) * offset);
    padded[offset] = -128;
    memset(padded + offset + 1, 0, num_zero_bytes);
}

void write_big_endian_uint64_to_mem_location(uint64 value, void *location)
{
    for (int i = 1; i <= 8; ++i)
    {
        *((((char*)location) + (8 - i))) = 0xff & value;
        value >>= 8;
    }
}
