//
//  MaxHeap.hpp
//  Algorithm
//
//  Created by nchkdxlq on 2017/8/6.
//  Copyright © 2017年 nchkdxlq. All rights reserved.
//

#ifndef MaxHeap_hpp
#define MaxHeap_hpp

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <iostream>

using namespace std;

template<typename Item>
class MaxHeap {
    
    
private:
    Item *m_data;
    int m_count;
    int m_capacity;
    
    void shiftUp(int k) {
        while (k > 1 && m_data[k/2] < m_data[k]) {
            swap(m_data[k/2], m_data[k]);
            k /= 2;
        }
    }
    
    void shiftDown(int k) {
        while (k <= m_count) {
            int j = 2*k;
            
            if (j+1 <= m_count && m_data[j+1] > m_data[j])
                j = j+1;
            
            if (m_data[j] <= m_data[k])
                break;
            
            swap(m_data[j], m_data[k]);
            k = j;
        }
    }
    
    
    void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){
        
        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if( num >= 10 ) {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else{
            if( isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }
    
    void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){
        
        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        assert( offset_left + 1 < line.size() );
        int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert( offset_right < line.size() );
        
        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

    
public:
    MaxHeap(int capacity) {
        m_data = new Item[capacity + 1];
        m_capacity = capacity;
        m_count = 0;
    }
    
    int size() {
        return m_count;
    }
    
    bool isEmpty() {
        return m_count == 0;
    }

    void insert(Item item) {
        assert(m_capacity >= m_count+1);
        
        m_data[++m_count] = item;
        shiftUp(m_count);
    }
    
    Item extractMax() {
        assert(m_count > 0);
        
        Item ret = m_data[1];
        m_data[1] = m_data[m_count];
        m_data[m_count] = NULL;
        m_count--;
        
        shiftDown(1);

        return ret;
    }
    
    void testPrint(){
        
        if( size() >= 100 ){
            cout<<"Fancy print can only work for less than 100 int";
            return;
        }
        
        if( typeid(Item) != typeid(int) ){
            cout <<"Fancy print can only work for int item";
            return;
        }
        
        cout<<"The Heap size is: "<<size()<<endl;
        cout<<"data in heap: ";
        for( int i = 1 ; i <= size() ; i ++ )
            cout<<m_data[i]<<" ";
        cout<<endl;
        cout<<endl;
        
        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while( n > 0 ) {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }
        
        int max_level_number = int(pow(2, max_level-1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for( int level = 0 ; level < max_level ; level ++ ){
            string line1 = string(max_level_number*3-1, ' ');
            
            int cur_level_number = min(m_count-int(pow(2,level))+1,int(pow(2,level)));
            bool isLeft = true;
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                putNumberInLine( m_data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                isLeft = !isLeft;
            }
            cout<<line1<<endl;
            
            if( level == max_level - 1 )
                break;
            
            string line2 = string(max_level_number*3-1, ' ');
            for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
            cout<<line2<<endl;
            
            cur_tree_max_level_number /= 2;
        }
    }
    
    ~MaxHeap() {
        delete [] m_data;
        m_data = NULL;
    }
};



#endif /* MaxHeap_hpp */
