//
//  util.h
//  HashUtility
//
//  Created by Achoual Othmane on 02/10/2018.
//  Copyright © 2018 Achoual Othmane. All rights reserved.
//

#ifndef util_h
#define util_h

#include <cstring>

typedef unsigned long long uint64;

unsigned int left_rotate(unsigned int x, unsigned int c);
unsigned int right_rotate(unsigned int x, unsigned int c);

unsigned int get_padded_length_in_bits(unsigned int plain_length);

void pad(const char *plain, char *padded, unsigned int offset, size_t num_zero_bytes);

void write_big_endian_uint64_to_mem_location(uint64 value, void *location);

unsigned int as_big_endian(unsigned int le);
#endif /* util_h */
