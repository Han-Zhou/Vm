#ifndef ACTIONTYPES_H
#define ACTIONTYPES_H

enum ActionTypes {

    // simple cursor movements
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,

    // moves to words
    MOVE_WORD_W,
    MOVE_WORD_B,
    MOVE_WORD_BIG_W,
    MOVE_WORD_BIG_B,

    // moves regarding lines
    MOVE_LINE_0,
    MOVE_LINE_$,
    MOVE_LINE_caret, // ^






    // changes modes
    CHANGE_TO_INSERT_I,
    CHANGE_TO_INSERT_A,
    CHANGE_TO_INSERT_O,
    CHANGE_TO_INSERT_BIG_I,
    CHANGE_TO_INSERT_BIG_A,
    CHANGE_TO_INSERT_BIG_O,

    CHANGE_TO_NORMAL,





};

#endif