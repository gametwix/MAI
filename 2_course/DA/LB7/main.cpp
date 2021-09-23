#include <iostream>
#include <string>
#include <cstring>

uint64_t Variants(std::string &str,uint64_t presum[100][100], int i, int j){
    if(j < i){
        return 0;
    } else {
        if(str[i] == str[j]){
            if(presum[i][j] == 0){
                presum[i][j] = Variants(str,presum,i + 1,j) + Variants(str,presum,i,j - 1) + 1;
            }
            return presum[i][j];
        } else {
            if(presum[i][j] == 0){
                presum[i][j] = Variants(str,presum,i + 1,j) + Variants(str,presum,i,j - 1) - Variants(str,presum,i + 1,j - 1);
            }
            return presum[i][j];
        }
    }
}

int main(){
    uint64_t presum[100][100];
    std::memset(presum,0,sizeof(uint64_t)*10000);
    std::string str;
    std::cin >> str;
    std::cout << Variants(str,presum,0,str.size() - 1) << std::endl;
    return 0;
}