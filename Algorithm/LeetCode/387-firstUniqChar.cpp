//
//  387-firstUniqChar.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2019/6/14.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "387-firstUniqChar.hpp"
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef pair<int, int> IIPair;

int firstUniqChar(string s) {
    int len = (int)s.length();
    if (len == 0) return -1;
    if (len == 1) return 0;
    
    // pair<int, int> 频次，第一次出现的index
    unordered_map<char, IIPair> mp;
    // 统计字符出现的频次和第一次出现的下标
    for (int i = 0; i < len; i++) {
        if (mp.find(s[i]) != mp.end()) {  // 出现过
#if 0
            mp[s[i]].first++;
#else
            IIPair &p = mp[s[i]];
            p.first++;
#endif
        } else {
            auto newp = IIPair(1, i);
            mp[s[i]] = newp;
        }
    }
    
    int ret = -1;
    
    // 找到出现频次为1，最小的下标
    for (auto item : mp) {
        IIPair p = item.second;
        if (p.first == 1) {
            if (ret > -1) {
                if (p.second < ret) {
                    ret = p.second;
                }
            } else {
                ret = p.second;
            }
        }
    }
    
    return ret;
}


void __387_entry() {
    string str = "loveleetcode";
    int ret = firstUniqChar(str);
    cout << "ret = " << ret << endl;
    
    unordered_map<int, int> mp;
    mp[1] = 100;
    
    mp[1]++; //有效
    
    mp[1] += 1; //有效
    
    auto i = mp[1]; //无效 (坑)
    i++;
    
    int &i2 = mp[1]; //有效
    i2++;
    
    cout << mp[1] << endl;
}
