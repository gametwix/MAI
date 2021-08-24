#include "SuffTree.hpp"

#include <iostream>
#include <memory>

int main(){
    std::string text;
    std::cin >> text;
    TSuffTree Trie;
    Trie.Init(text);
    Trie.Print();
    return 0;
}