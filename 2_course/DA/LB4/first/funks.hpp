#include <iostream>
#include <vector>
#include "ahok.hpp"

size_t CreateBor(TAhoKarasik &ahk)
{
    struct SPattern{
        std::vector<long long> Pattern;
        size_t Pos_start;
    };

    size_t pos = 0;
    long long num = 0;
    size_t pattern_count = 0;
    size_t ch;
    bool in_num = false;
    bool in_pat = false;
    std::vector<SPattern*> patterns;
    SPattern* cur_pattern = new SPattern();
    char in;
    while(std::cin.get(in)){
        ch = in;
        if(ch == 63){
            pos++;
            patterns.push_back(cur_pattern);
            cur_pattern = new SPattern();
            in_pat = false;
        }
        else if((ch>47)&&(ch<58)){
            num *= 10;
            num += ch-48;
            in_num = true;
            
        }
        else if(ch == 32 && in_num){
            in_num = false;
            if(!in_pat){
                cur_pattern->Pos_start = pos;
                in_pat = true;
            }
            cur_pattern->Pattern.push_back(num);
            num = 0;
            ++pos;
        }
        if(ch == 10){
            if(!in_pat)
                cur_pattern->Pos_start = pos;
            if(in_num)
                cur_pattern->Pattern.push_back(num);
            patterns.push_back(cur_pattern);
            break;
        }
    }
    if(patterns.empty())
        delete cur_pattern;    
    for(auto i:patterns){
        ahk.Push(i->Pattern,i->Pos_start);
        ++pattern_count;
        delete(i);
    }
    ahk.SearchSufPtr();
    return pattern_count;
}

void ReadText(std::vector<long long> &text,std::vector<int> &size_line){
    char ch;
    long long num = 0;
    int num_word = 0;
    bool in_num = false;
    while(std::cin.get(ch)){
        int in = ch;
        if((in>47)&&(in<58)){
            num *= 10;
            num += in-48;
            in_num = true;
        }
        else if(in == 32 && in_num){
            in_num = false;
            text.push_back(num);
            num = 0;
            ++num_word;
        }
        else if(in == 10){
            if(in_num){
                in_num = false;
                text.push_back(num);
                num = 0;
                ++num_word;
            }
            size_line.push_back(num_word-1);
        }
    }
    if(in_num){
                in_num = false;
                text.push_back(num);
                num = 0;
                ++num_word;
            }
            size_line.push_back(num_word-1);
}

std::vector<int> Compact_size_text(std::vector<int> size_line){
    std::vector<int> new_vect;
    int last = -1;
    int size = size_line.size();
    for(size_t i = 0;i < size;++i){
        if(size_line[i] != last){
            last = size_line[i];
            new_vect.push_back(last);
        }
    }
    return new_vect;
}