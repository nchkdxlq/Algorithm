//
//  FileOps.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/3.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef FileOps_hpp
#define FileOps_hpp

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace FileOps {
    bool readFile(const string& filename, vector<string> &words);
}

#endif /* FileOps_hpp */
