#include <iostream>
#include "SuffTree.h"

int main(){
    std::string str;
    std::cin >> str;
    TSuffTree tree(str);
    int i = 1;
    while(std::cin >> str){
        std::vector<int> ans;
        tree.Find(str,ans);
        if(!ans.empty()){
            std::cout << i << ": " << ans[0];
            for(int j = 1;j < ans.size();++j){
                std::cout << ", " << ans[j];
            }
            std::cout << std::endl;
        }
        ++i;
    }
    return 0;
}