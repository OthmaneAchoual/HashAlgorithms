//
//  md5.cpp
//  HashUtility
//
//  Created by Achoual Othmane on 02/10/2018.
//  Copyright © 2018 Achoual Othmane. All rights reserved.
//

#include "md5.h"
#include "util.h"

#include <cmath>
#include <iostream>
#include <cstring>

char *md5(const char *plain){
    char *digest = new char[16];
    
    unsigned int r[] = {
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    
    unsigned int k[64];
    for (int i = 0; i < 64; ++i)
    {
        k[i] = floor((1ll << 32) * abs(sin(i + 1)));
    }
    
    unsigned int a0 = 0x67452301;
    unsigned int b0 = 0xefcdab89;
    unsigned int c0 = 0x98badcfe;
    unsigned int d0 = 0x10325476;
    
    unsigned int plain_length = strlen(plain);
    unsigned int padded_length_in_bits = get_padded_length_in_bits(plain_length);
    
    unsigned int padded_length_in_bytes = padded_length_in_bits / 8;
    char *bits = new char[padded_length_in_bytes];
    
    pad(plain, bits, plain_length, padded_length_in_bytes - (plain_length + 1));
    
    *((long long *)&bits[padded_length_in_bytes - 8]) = plain_length * 8;
    
    for (int l = 0; l < padded_length_in_bytes / 64; ++l)
    {
        unsigned int a = a0;
        unsigned int b = b0;
        unsigned int c = c0;
        unsigned int d = d0;
        
        for (int i = 0; i < 64; ++i)
        {
            unsigned int f, g;
            if (i >= 0 && i <= 15)
            {
                f = (b & c) | ((~b) & d);
                g = i;
            }
            else if (i >= 16 && i <= 31)
            {
                f = (d & b) | ((~d) & c);
                g = (5 * i + 1) % 16;
            }
            else if (i >= 32 && i <= 47)
            {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            }
            else
            {
                f = c ^ (b | (~d));
                g = (7 * i) % 16;
            }
            unsigned int m = *((unsigned int*)(&bits[l * 64 + (g * 4)]));
            f = f + a + k[i] + m;
            a = d;
            d = c;
            c = b;
            b = b + left_rotate(f, r[i]);
        }
        a0 += a;
        b0 += b;
        c0 += c;
        d0 += d;
    }
    
    memcpy(digest     , &a0, sizeof(unsigned int));
    memcpy(digest + 4 , &b0, sizeof(unsigned int));
    memcpy(digest + 8 , &c0, sizeof(unsigned int));
    memcpy(digest + 12, &d0, sizeof(unsigned int));
    
    delete[] bits;
    return digest;
}
