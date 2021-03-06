//
//  FileOps.cpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/9/3.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#include "FileOps.hpp"
#include <iostream>
#include <fstream>

using namespace std;

namespace FileOps {
    
    int firstCharacterIndex(const string& s, int start){
        for (int i = start; i < s.length(); i ++) {
            if( isalpha(s[i]) )
                return i;
        }
        
        return int(s.length());
    }
    
    string lowerS(const string& s) {
        
        string ret = "";
        for (int i = 0; i < s.length(); i++)
            ret += tolower(s[i]);
        
        return ret;
    }
    
    bool readFile(const string& filename, vector<string> &words) {
        
        string line;
        string contents = "";
        ifstream file(filename);
        if (file.is_open()) {
            while (getline(file, line))
                contents += ( line + "\n" );
            file.close();
        } else {
            cout<<"Can not open "<<filename<<" !!!"<<endl;
            return false;
        }
        
        int start = firstCharacterIndex(contents, 0);
        
        for (int i = start + 1; i <= contents.length(); ) {
            
            if (i == contents.length() || !isalpha(contents[i])) {
                words.push_back(lowerS(contents.substr(start,i-start)));
                start = firstCharacterIndex(contents, i);
                i = start + 1;
            } else {
                i++;
            }
        }
        
        return true;
    }
}


