#include <iostream>
#include <vector>
#include <algorithm>


int main(){
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    int sum[3] = {0,0,0};
    int count = 0;
    int size = nums.size();
    int countthree = 0;
    for(auto &i:nums){
        std::cin >> i;
        ++sum[i - 1];
    } 
    for(int i = 0; i < sum[0]; ++i){
        if(nums[i] != 1)
            ++count;
    }
    for(int i = sum[0]; i < sum[0]+sum[1]; ++i){
        if(nums[i] == 3){
            ++count;
            --countthree;
        }
    }
    for(int i = sum[0]+sum[1]; i < size; ++i){
        if(nums[i] == 2)
            ++countthree;
    }
    count += countthree;
    std::cout << count << std::endl;
    return 0;
}