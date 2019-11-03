//
// Created by ali-64142 on 2019-11-02.
//

#include "Element.h"
#include <iostream>
using namespace std;
bool Element::changeFlag = true;
Element::Element(int i) {
    setValue(i);
};
Element::Element() {
    setValue(0);
};
void Element::checkDone() {
    if(getValue() != 0 ) {
//        cout << "already done" << endl;
        return;
    }
    for (int i = 0; i < 9; i++) {
        int tmp = value >> 16;
        if( tmp == (1 << i)) {
            setValue(i+1);
            return;
        }
    }
}
bool Element::isPossible(int i) {
    return (value & ((1 << 16) << (i -1))) != 0;
}
void Element::clearPossible(int i) {
    if (i == 0 || getValue() !=0) {
        return;
    }
    int oldValue = value;
    value &= ~((1<< 16) << (i -1));
    if (oldValue != value) {
        changeFlag = true;
    }
    checkDone();
}

void Element::clearMultipleFlags(int flags){
    int oldValue = value;
    value &= ~(flags<<16);
    if (oldValue != value) {
        changeFlag = true;
    }
    checkDone();
}
void Element::setValue(int i) {
//    if(value & 0xf != 0) {
//        cout << "set value error, value is already set" << endl;
//        return;
//    }
    if(i == 0 ) {
        value = 0x1ff << 16;
    } else {
        value = i;
        changeFlag = true;
//        cout << "set value:" << value << endl;
    }
}

void Element::dumpPossibleValues() {
    if (getValue() != 0) {
        cout << getValue() << endl;
        return;
    }
    for(int i = 1; i< 10; i++) {
        if(isPossible(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int Element::getPossibleCount() {
    if (getValue() != 0) {
        return 1;
    }
    int val = value >> 16;
    int ret = 0;
    for (int i = 0; i < 9; i++) {
        if (val & 1 << i) {
            ret ++;
        }
    }
    return ret;
}
int Element::getPossibleRaw() {
    if (getValue() != 0) {
        return 1<< getValue();
    } else {
        return value >> 16;
    }
}