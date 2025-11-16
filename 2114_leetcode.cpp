#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector <std::string> sentences = {"alice and bob love leetcode", "i think so too", "this is great thanks very much"};


void foo(std::vector <std::string> sentences) {
    int result = 1;
    int pred_result = 0;
    int answer;
    for(int i = 0; i < sentences.size(); i++) {
        for(int j = 0; j < sentences.at(i).size(); j++) {
            if(sentences.at(i).at(j) == ' ') {
                result++;
            }
        }
        if(result > pred_result) {
            answer = result;
        }
        result = pred_result;
        result = 1;
    }
    std::cout << answer;
}

int main() {
    foo(sentences);
}
