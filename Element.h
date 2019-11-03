//
// Created by ali-64142 on 2019-11-02.
//

#ifndef UNTITLED1_ELEMENT_H
#define UNTITLED1_ELEMENT_H


class Element {
private:
    int value;
public:
    static bool changeFlag;
    Element(int i);
    Element();
    void checkDone();
    bool isPossible(int i);
    void clearPossible(int i);
    void setValue(int i);
    int getValue() {return value & 0xf;}
    void dumpPossibleValues();
    int getPossibleCount();
    int getPossibleRaw();
    void clearMultipleFlags(int flags);
};


#endif //UNTITLED1_ELEMENT_H
