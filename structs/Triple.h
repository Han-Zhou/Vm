#ifndef TRIPLE_H


#define TRIPLE_H


struct Triple {
    int line;
    int subLine;
    int index;

    Triple(int l, int s, int i) : line{l}, subLine{s}, index{i} { }

    Triple(const Triple &t) = default;
    Triple(Triple &&t) = default;
    Triple &operator=(const Triple &t) = default;
    Triple &operator=(Triple &&t) = default;
};




#endif