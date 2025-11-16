#include <iostream>
#include <vector>

std::vector <int> nums = {1,2,3,1,1,3};
int result = 0;

void foo(std::vector <int> nums) {
    for(int i = 0; i < nums.size(); i++) {
        for(int j = 1; j < nums.size(); j++) {
            if(nums.at(i) == nums.at(j) && j > i) {
                result++;
            }
        }
    }
    std::cout << result;
}


int main() {
    foo(nums);
}