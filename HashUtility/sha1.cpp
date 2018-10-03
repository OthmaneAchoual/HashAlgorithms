//
//  sha1.cpp
//  HashUtility
//
//  Created by Achoual Othmane on 03/10/2018.
//  Copyright © 2018 Achoual Othmane. All rights reserved.
//

#include "sha1.h"
#include "util.h"

#include <cstring>

char *sha1(const char *plain)
{
    char *digest = new char[20];
    
    unsigned int h0 = 0x67452301;
    unsigned int h1 = 0xefcdab89;
    unsigned int h2 = 0x98badcfe;
    unsigned int h3 = 0x10325476;
    unsigned int h4 = 0xc3d2e1f0;
    
    unsigned int plain_length = strlen(plain);
    uint64 plain_length_in_bits = plain_length * 8;
    unsigned int padded_length_in_bits = get_padded_length_in_bits(plain_length);
    unsigned int padded_length_in_bytes = padded_length_in_bits / 8;
    
    char *padded = new char[padded_length_in_bytes];
    pad(plain, padded, plain_length, padded_length_in_bytes - (plain_length + 1));
    write_big_endian_uint64_to_mem_location(plain_length_in_bits, &padded[padded_length_in_bytes - 8]);
    
    for (int j = 0; j < padded_length_in_bytes / 64; ++j)
    {
        unsigned int *w = new unsigned int[80];
        memcpy(w, &padded[j * 64], 64);
        for (int i = 0; i < 16; ++i)
        {
            w[i] = as_big_endian(w[i]);
        }
        for (int i = 16; i < 80; ++i)
        {
            w[i] = left_rotate(w[i - 3] ^ w[i - 8] ^ w[i -14] ^ w[i - 16], 1);
        }
        
        unsigned int a = h0;
        unsigned int b = h1;
        unsigned int c = h2;
        unsigned int d = h3;
        unsigned int e = h4;
        unsigned int f, k;
        
        for (int i = 0; i < 80; ++i)
        {
            if (i >= 0 && i <= 19)
            {
                f = (b & c) | ((~b) & d);
                k = 0x5a827999;
            }
            else if (i >= 20 && i <= 39)
            {
                f = b ^ c ^ d;
                k = 0x6ed9eba1;
            }
            else if (i >= 40 && i <= 59)
            {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8f1bbcdc;
            }
            else
            {
                f = b ^ c ^ d;
                k = 0xca62c1d6;
            }
            unsigned int tmp;
            tmp = left_rotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = left_rotate(b, 30);
            b = a;
            a = tmp;
        }
        
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        
        delete[] w;
    }
    
    for (int i = 0; i < 4; ++i)
    {
        digest[i] = (h0 >> (3 - i) * 8) & 0xff;
        digest[i + 4] = (h1 >> (3 - i) * 8) & 0xff;
        digest[i + 8] = (h2 >> (3 - i) * 8) & 0xff;
        digest[i + 12] = (h3 >> (3 - i) * 8) & 0xff;
        digest[i + 16] = (h4 >> (3 - i) * 8) & 0xff;
    }
    
    delete[] padded;
    return digest;
}
