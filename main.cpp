#include <iostream>
#include <fstream>
#include "Element.h"
#include "deduce.h"
#include "combination.h"
#define USE_FILE
using namespace std;
int main() {
    Element orig[9][9];
#ifdef USE_FILE
    char arr[10];
    string input;
    ifstream fin("/Users/han/test/input1.txt");
    for (int i = 0; i < 9; i++) {
        fin.getline(arr, 10);
        arr[9] = 0;
        input = arr;
//        cout << input << endl;
        for (int j = 0; j < 9; j++) {
            int value = input[j] -'0';
            if (value > 9 || value < 0) {
                cout << "invalid value" << value << endl;
                return -1;
            }
            orig[i][j].setValue(value);
//            cout <<"i:" << i << " j:" << j << " set value: " << value << "  get value: " << orig[i][j].getValue() << endl;
//            orig[3][8].dumpPossibleValues();
        }
    }

    fin.close();
#else
    std::cout << "input original sudoku:" << std::endl;
    string input;
    for (int i = 0; i < 9; i++) {
        getline(cin, input);
        if(input.length() < 9) {
            cout << "input size too short" << endl;
            i --;
            continue;
        }
        for (int j = 0; j < 9; j++) {
            int value = input[j] -'0';
            if (value > 9 || value < 0) {
                cout << "invalid value" << value << endl;
                i --;
                break;
            }
            orig[i][j].setValue(value);
        }
    }
#endif
    Element result[9][9];
    memcpy(result, orig, sizeof(orig));
    deduce(result);
    printResult(result);
//    combinationTest();
    return 0;
}