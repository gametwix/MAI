#include "ahok.hpp"
#include <iostream>
#include <vector>


int ReadPattern(TAhoKorasik &ahok){
    char ch;
    int ind;
    int pos_pattern = 0;
    bool innum = false;
    long long num = 0;
    int num_pattern = 0;
    std::vector<long long> pattern;
    while(std::cin.get(ch)){
        ind = ch;
        if(ind > 47 && ind < 58){
            innum = true;
            num *= 10;
            num += ind - 48;
        }
        if(ind == 32 && innum){
            ++pos_pattern;
            pattern.push_back(num);
            num = 0;
            innum = false;
        }
        if(ind == 63){
            if(!pattern.empty())
            {
                ahok.Push(pattern,pos_pattern-1);
                ++num_pattern;
                pattern.clear();
                ++pos_pattern;
            }
            else
                ++pos_pattern;
        }
        if(ind == 10){
            if(innum){
                ++pos_pattern;
                pattern.push_back(num);
                num = 0;
                innum = false;
            }
            ahok.Push(pattern,pos_pattern-1);
            ++num_pattern;
            break;
        }
    }
    return num_pattern;
}


void ReadText(std::vector<SText> &text)
{
    char ch;
    int ind;
    int numelem = 1;
    int numsrt = 1;
    long long num = 0;
    bool innum = false;
    SText word;
    while(std::cin.get(ch)){
        ind = ch;
        if(ind > 47 && ind < 58){
            innum = true;
            num *= 10;
            num += ind - 48;
        }
        if(ind == 32 && innum){
            innum = false;
            word.Sym = num;
            word.str = numsrt;
            word.word = numelem;
            text.push_back(word);
            ++numelem;
            num = 0;
        }
        if(ind == 10){
            if(innum)
            {
                innum = false;
                word.Sym = num;
                word.str = numsrt;
                word.word = numelem;
                text.push_back(word);
                ++numelem;
                num = 0;
            }
            ++numsrt;
            numelem = 1;
        }
    }
    if(innum)
    {
        word.Sym = num;
        word.str = numsrt;
        word.word = numelem;
        text.push_back(word);
    }
}

int main(){
    TAhoKorasik ahok;
    int num_pattern;
    std::vector<SText> text;
    num_pattern = ReadPattern(ahok);
    ReadText(text);
    int intext = text.size();
    std::vector<int> pos(intext);
    ahok.BorSuf();
    ahok.Find(text,pos);
    int size = pos.size();
    for(int i = 0;i < size;++i)
    {
        if(pos[i] == num_pattern)
        {
            std::cout << text[i].str << ", " << text[i].word <<std::endl;
        }
    }

    return 0;
}