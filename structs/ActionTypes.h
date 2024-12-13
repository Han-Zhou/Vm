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


    // undo and redo
    UNDO,
    REDO,

    // delete actions
    DELETE_DJ,
    DELETE_DK,
    DELETE_DH,
    DELETE_DL,

    DELETE_DW,
    DELETE_DBIGW,
    DELETE_DB,
    DELETE_DBIGB,
    DELETE_D$,
    DELETE_DCARET,
    DELETE_D0,

    DELETE_DD,


    // change actions
    CHANGE_CJ,
    CHANGE_CK,
    CHANGE_CH,
    CHANGE_CL,

    CHANGE_CW,
    CHANGE_CBIGW,
    CHANGE_CB,
    CHANGE_CBIGB,
    CHANGE_C$,
    CHANGE_CCARET,
    CHANGE_C0,

    CHANGE_CC,
 
    


    
    // paste actions
    PASTE_P,
    PASTE_BIGP,

    // delete actions
    YANK_YJ,
    YANK_YK,
    YANK_YH,
    YANK_YL,

    YANK_YW,
    YANK_YBIGW,
    YANK_YB,
    YANK_YBIGB,
    YANK_Y$,
    YANK_YCARET,
    YANK_Y0,

    YANK_YY,






    // changes modes
    CHANGE_TO_INSERT_I,
    CHANGE_TO_INSERT_A,
    CHANGE_TO_INSERT_O,
    CHANGE_TO_INSERT_BIG_I,
    CHANGE_TO_INSERT_BIG_A,
    CHANGE_TO_INSERT_BIG_O,

    CHANGE_TO_NORMAL,



    // colons
    COLON_WQ,
    COLON_Q,
    COLON_W,
    COLON_0,
    COLON_$,
    COLON_LINE,
    COLON_Q_EXCLAMATION,





};

#endif