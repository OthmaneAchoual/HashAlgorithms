//
//  main.cpp
//  HashUtility
//
//  Created by Achoual Othmane on 02/10/2018.
//  Copyright © 2018 Achoual Othmane. All rights reserved.
//

#include <iostream>
#include <string>

#include "md5.h"
#include "sha1.h"

int main(int argc, const char * argv[]) {
    if (argc == 3)
    {
        int digest_length;
        std::string algo = argv[1];
        char *digest;
        
        std::cout << argv[2] << std::endl;
        
        if (algo == "md5")
        {
            std::cout << "md5 chosen" << std::endl;
            digest_length = 16;
            digest = md5(argv[2]);
        } else {
            std::cout << "sha1 chosen" << std::endl;
            digest_length = 20;
            digest = sha1(argv[2]);
        }
        
        for (int i = 0; i < digest_length; ++i)
        {
            std::cout << std::hex << ((digest[i] >> 4) & 0xf);
            std::cout << std::hex << (digest[i] & 0xf);
        }
        std::cout << std::endl;
        
        delete[] digest;
    }
    else
    {
        std::cerr << "Usage: hash <algorithm> <plaintext>" << std::endl;
    }
    return 0;
}
