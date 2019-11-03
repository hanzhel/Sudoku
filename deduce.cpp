//
// Created by ali-64142 on 2019-11-02.
//
#include <iostream>
#include <vector>
#include "Element.h"
#include "combination.h"
#include "deduce.h"
using namespace std;
void GridRule(elementArray& input) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(input[i][j].getValue() != 0) {
                int val = input[i][j].getValue();
                int row = i/3;
                int column = j /3;
                int rowStart = row*3;
                int columnStart = column*3;
                input[rowStart][columnStart].clearPossible(val);
                input[rowStart][columnStart + 1].clearPossible(val);
                input[rowStart][columnStart + 2].clearPossible(val);
                input[rowStart + 1][columnStart].clearPossible(val);
                input[rowStart + 1][columnStart + 1].clearPossible(val);
                input[rowStart + 1][columnStart + 2].clearPossible(val);
                input[rowStart + 2][columnStart].clearPossible(val);
                input[rowStart + 2][columnStart + 1].clearPossible(val);
                input[rowStart + 2][columnStart + 2].clearPossible(val);
            }
        }
    }
}
void ColumnRule(elementArray& input) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(input[i][j].getValue() != 0)
                for (int k = 0; k < 9; k++) {
                input[k][j].clearPossible(input[i][j].getValue());
            }
        }
    }
}
void RowRule(elementArray& input) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(input[i][j].getValue() != 0)
            for (int k = 0; k < 9; k++) {
                input[i][k].clearPossible(input[i][j].getValue());
            }
        }
    }
}
void CheckOnlyRule(Element* p[9]) { // p should be array of element with 9 elements
//    for(int i = 0; i< 9; i++) cout << p[i]->getValue();
//    cout << endl;
    int pos = 0;
    int count = 0;
    for(int i = 1; i < 10; i++) { // i is value 1-9
        pos = 0; count = 0;
        for (int j = 0; j < 9; j++) {// j is index 0-8
            if (p[j]->getValue() == i) {
                count = 0;
                break;
            }
            if (p[j]->isPossible(i)) {
                pos = j;
                count ++;
            }
        }
        if(count == 1) {
            cout << "only rule setvalue " << i << endl;
            p[pos]->setValue(i);
        }
    }
}
void groupRule(Element* p[9]) { // p should be array of element with 9 elements
    // 2 same: find all count <= 2 and check whether we can find a 2*2 subset
    vector<int> raws(9);
    vector<int> indice;
//    cout << "start group rule:"<< endl;
    for (int i = 0; i < 9; i++) {
        raws[i] = p[i]->getPossibleRaw();
//        p[i]->dumpPossibleValues();
        if (p[i]->getPossibleCount() == 2) {
            indice.push_back(i);
        }
    }
    if (indice.size() >= 2) {
        //get all possible combinations
        auto combinations = getCombinations(indice, 2);
        for (auto it:combinations) {
            int rawValue = 0;
            for (int j = 0; j < 2; j++) {
                rawValue |= raws[it[j]];
            }
            int count = 0;
            for (int j = 0; j < 9; j++) {
                if((rawValue & 1<<j) != 0) {
                    count ++;
                }
            }
            if(count == 2) {
//                for (int indexIt:indice) {
//                    p[indexIt]->dumpPossibleValues();
//                }
                for (int i = 1; i < 9; i++) {
                    if (find(it.begin(), it.end(), i) == it.end()) {
                        p[i]->clearMultipleFlags(rawValue);
                    }
                }
                if (Element::changeFlag) {
//                    cout << "get result for group rule: dimension 2" << endl;
                    break;
                }
            }
        }
    }
//    cout << "end group rule:"<< endl;

    // 3 * 3 same
    indice.clear();
    for (int i = 0; i < 9; i++) {
        int count = p[i]->getPossibleCount();
        if ( count <= 3 && count >1) {
            indice.push_back(i);
        }
    }
    if (indice.size() >= 3) {
        //get all possible combinations
        auto combinations = getCombinations(indice, 3);
        for (auto it:combinations) {
            int rawValue = 0;
            for (int j = 0; j < 3; j++) {
                rawValue |= raws[it[j]];
            }
            int count = 0;
            for (int j = 0; j < 9; j++) {
                if((rawValue & 1<<j) != 0) {
                    count ++;
                }
            }
            if(count == 3) {
                int changeFlagBak = Element::changeFlag;
                Element::changeFlag = false;
                for (int i = 1; i < 9; i++) {
                    if (find(it.begin(), it.end(), i) == it.end()) {
                        p[i]->clearMultipleFlags(rawValue);
                    }
                }
                if (Element::changeFlag) {
                    cout << "get result for group rule: dimension 3" << endl;
                    break;
                }
                Element::changeFlag = changeFlagBak;
            }
        }
    }
    // 4* 4 same
    indice.clear();
//       cout << "start for rule 4:" << endl;
    for (int i = 0; i < 9; i++) {
        int count = p[i]->getPossibleCount();
//           p[i]->dumpPossibleValues();
        if ( count <= 4 && count >1) {
            indice.push_back(i);
        }
    }
    if (indice.size() >= 4) {
        auto combinations = getCombinations(indice, 4);
        for (auto it:combinations) {
            int rawValue = 0;
            for (int j = 0; j < 4; j++) {
                rawValue |= raws[it[j]];
            }
            int count = 0;
            for (int j = 0; j < 9; j++) {
                if((rawValue & 1<<j) != 0) {
                    count ++;
                }
            }
            if(count == 4) {
                int changeFlagBak = Element::changeFlag;
                Element::changeFlag = false;
                for (int i = 1; i < 9; i++) {
                    if (find(it.begin(), it.end(), i) == it.end()) {
                        p[i]->clearMultipleFlags(rawValue);
                    }
                }
                if (Element::changeFlag) {
                    cout << "get result for group rule: dimension 4" << endl;
                    break;
                }
                Element::changeFlag = changeFlagBak;
            }
        }
    }
}

void CheckOnlyRule(elementArray& input) {
    //row
    for (int i = 0; i < 9; i++) {
        Element* p[9] = {&input[i][0], &input[i][1], &input[i][2],
                         &input[i][3], &input[i][4], &input[i][5],
                         &input[i][6], &input[i][7], &input[i][8]};
        CheckOnlyRule(p);
        groupRule(p);
    }
    //column
    for (int j = 0; j < 9; j++) {
        Element* p[9] = {&input[0][j], &input[1][j], &input[2][j],
                         &input[3][j], &input[4][j], &input[5][j],
                         &input[6][j], &input[7][j], &input[8][j]};
        CheckOnlyRule(p);
        groupRule(p);
    }
    //grid
    for(int i = 0; i < 9; i ++) {
        int x = i/3;
        int y = i%3;
        Element* p[9] = {&input[3*x][3*y], &input[3*x][3*y+1], &input[3*x][3*y+2],
                         &input[3*x+1][3*y], &input[3*x+1 ][3*y+1], &input[3*x+1][3*y+2],
                         &input[3*x+2][3*y], &input[3*x+2][3*y+1], &input[3*x+2][3*y+2]};
        CheckOnlyRule(p);
        groupRule(p);
    }
}
void deduce(elementArray& input) {
    int i = 0;
    while (Element::changeFlag) {
        Element::changeFlag = false;
        cout << "round: " << i ++ << endl;
        GridRule(input);
        ColumnRule(input);
        RowRule(input);
        CheckOnlyRule(input);
    }
    return;
}

void printResult(elementArray &input) {
    for (int i = 0; i < 9; i++) {
        if(i%3 == 0) {
            cout << "-------------------" << endl;
        }
        cout << "|";
        for (int j = 0; j < 9; j++) {
            char c = ' ';
            if((j +1) %3 == 0) c = '|';
            cout << input[i][j].getValue() << c;
        }
        cout << endl;
    }
    cout << "-------------------" << endl;
}