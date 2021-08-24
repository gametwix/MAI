#include"Trie.h"
#include"text.h"
#include <iostream>
#include<vector>

int main()
{
    TTrie trie;
    std::vector<std::pair<int, std::vector<uint32_t>>> lk;
    ReadPattern(lk);
    trie.Create(lk);

    std::vector<std::pair<uint32_t, std::pair<int, int>>> text;
    ReadText(text);
    std::vector<std::pair<int, int>> out;
    trie.Find(text, out);
    for (auto& item : out) {
        std::cout << item.first << ", " << item.second<<std::endl;
    }
}