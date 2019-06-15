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

int firstUniqChar(string s) {
    int len = (int)s.length();
    if (len == 0) return -1;
    if (len == 1) return 0;
    
    // pair<int, int> 频次，第一次出现的index
    unordered_map<char, pair<int, int>> mp;
    // 统计字符出现的频次和第一次出现的下标
    for (int i = 0; i < len; i++) {
        auto item = s[i];
        int index = i;
        int count = 1;
        if (mp.find(item) != mp.end()) {  // 出现过
            pair<int, int> p = mp[item];
            count = ++p.first; // 频次加一
            index = p.second;
        }
        auto newp = make_pair(count, index);
        mp[item] = newp;
    }
    
    int ret = -1;
    
    // 找到出现频次为1，最小的下标
    for (auto item : mp) {
        pair<int, int> p = item.second;
        cout << item.first << " " << p.first << " " << p.second << endl;
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
}
