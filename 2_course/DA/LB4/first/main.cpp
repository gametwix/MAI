#include <iostream>
#include <vector>
#include "ahok.hpp"
#include "funks.hpp"


int main()
{
    size_t pattern_count;
    TAhoKarasik ahk;
    pattern_count = CreateBor(ahk);
    std::vector<long long> text;
    std::vector<int> size_line;
    ReadText(text,size_line);
    std::vector<int> pos_incl(text.size());
    ahk.Find(text,pos_incl);
    size_line = Compact_size_text(size_line);
    size_t size_text = pos_incl.size();
    for(size_t i = 0;i < size_text;++i){
        if(pos_incl[i]==pattern_count){
            size_t size_abz = size_line.size();
            if(i>=size_line[size_abz-1]){
                std::cout<<size_abz<<", "<< i - size_line[size_abz-1] +1  <<std::endl;
            }
            else{
                for(int j = 0; j<size_abz-1;++j){
                    if(i>=size_line[j] && i<size_line[j+1]){
                        std::cout<< j+1<<", "<< i - size_line[j] +1  <<std::endl;
                    }
                }
            }
        }
    }
    return 0;	
}