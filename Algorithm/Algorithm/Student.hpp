//
//  Student.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/7/18.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef Student_hpp
#define Student_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::ostream;

struct Student {
    
    string name;
    int score;
    
    bool operator<(const Student &other) {
        return score < other.score;
    }
    
    friend ostream& operator<<(ostream &os, const Student &stu) {
        os << "{ name = " << stu.name << " score = " << stu.score << " }";
        return os;
    }
};

#endif /* Student_hpp */
