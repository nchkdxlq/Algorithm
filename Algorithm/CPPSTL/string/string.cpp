//
//  string.cpp
//  CPPSTL
//
//  Created by Knox on 2019/7/11.
//  Copyright © 2019 nchkdxlq. All rights reserved.
//

#include "string.hpp"
#include <string>
#include <iostream>
#include <vector>

using namespace std;


void __init() {
    //变量 s1 只是定义但没有初始化，编译器会将默认值赋给 s1，默认值是""，也即空字符串。
    string s1;
    
    //变量 s2 在定义的同时被初始化为"c plus plus"。与C风格的字符串不同，string 的结尾没有结束标志'\0'。
    string s2 = "c plus plus";
    
    // 变量 s3 在定义的时候直接用 s2 进行初始化，因此 s3 的内容也是"c plus plus"。
    string s3 = s2;
    
    //变量 s4 被初始化为由 5 个's'字符组成的字符串，也就是"sssss"。
    string s4(5, 's');
    
    string s5("Hello World");
    
    // 使用字符数组初始化string
    vector<char> chars = {'S', 'w', 'i', 'f', 't'};
    string s6(chars.begin(), chars.end());
    
    
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;
    cout << s4 << endl;
    cout << s5 << endl;
    cout << s6 << endl;
}



void __iterator() {
    string s = "123456789";
    
    cout << "----- for range -----" << endl;
    for (auto item : s) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << "----- begin() - end() -----" << endl;
    for (auto i = s.begin(); i != s.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    
    cout << "----- rbegin() - rend() -----" << endl;
    for (auto i = s.rbegin(); i != s.rend(); i++) {
        cout << *i << " ";
    }
    cout << endl;
    
    cout << "----- operator[] -----" << endl;
    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << " ";
    }
    cout << endl;
}

void __size()
{
    string s1 = "www.baidu.com";
    
    // size/length都是返回string对象中字符的个数，字符串长度
    cout << "length = " << s1.length() << endl;
    cout << "size = " << s1.size() << endl;
    
    // 判空
    cout << (s1.empty() ? "is empty" : "is not empty") << endl;
    
    // 在不扩容的情况下，字符串可容纳字符的最大个数  容量
    cout << "capacity = " << s1.capacity() << endl;
    
    sort(s1.begin(), s1.end());
}


vector<string> commonChars(vector<string>& A) {
    int counter[26] = {};
    for (int i = 0; i < 26; i++) counter[i] = INT_MAX;
    vector<string> ret;
    
    for (auto &s : A) {
        int word[26] = {0};
        
        for (auto c : s) {
            word[c-'a'] = word[c-'a'] + 1;
        }
        
        for (int i = 0; i < 26; i++) {
            counter[i] = min(counter[i], word[i]);
        }
    }
    
    for (int i = 0; i < 26; i++) {
        int j = 0;
        while (j < counter[i]) {
            string s(1,('a'+i));
            ret.push_back(s);
            j++;
        }
    }
    
    return ret;
}


void string_entry() {
    __init();
    __size();
    __iterator();
    
    string s1 = "bella";
    string s2 = "label";
    string s3 = "roller";
    
    vector<string> strList{s1, s2, s3};
    vector<string> ret = commonChars(strList);
    
    auto a = tolower('A'); // a
    auto b = toupper('b'); // B
}
