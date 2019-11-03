//
// Created by ali-64142 on 2019-11-03.
//
#include "combination.h"
#include <iostream>
vector<vector<int>> getCombinations(const vector<int>& input, int dimension) {
    vector<vector<int>> ret;
    int size = input.size();
    if (dimension <= 0) {
        vector<int> tmp;
        ret.push_back(tmp);
        return ret;
    }
    if (size == dimension) {
        vector<int> element;
        for (int i = 0; i < dimension; i++) {
            element.push_back(input[i]);
        }
        ret.push_back(element);
        return ret;
    } else if(size > dimension){
        // last not included, dimenson unchanged
        ret = getCombinations({input.begin(), input.end() -1}, dimension);
        // last included , dimension -1
        auto ret1 = getCombinations({input.begin(), input.end() -1 }, dimension -1);
        for (auto it:ret1) {
            it.push_back(input[size -1]);
            ret.push_back(it);
        }
        return ret;
    } else {
        cout << "error in combination" << endl;
        return ret;
    }
}

void combinationTest() {
    vector<int> input = {2,3,4,5};
    auto ret = getCombinations(input, 2);
    cout << "combinationTest" << endl;
    for (auto it:ret) {
        for (auto it1 : it) {
            cout << it1;
        }
        cout << endl;
    }
}