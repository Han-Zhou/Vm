#include "CursorMover.h"

namespace controller {
    
        void CursorMover::moveUp(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                cursor.moveUp(window.getCOLS());
            }
        }
    
        void CursorMover::moveDown(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                cursor.moveDown(window.getLINES() - 1, window.getCOLS());
            }
        }
    
        void CursorMover::moveLeft(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                cursor.moveLeft(window.getCOLS());
            }
        }
    
        void CursorMover::moveRight(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                cursor.moveRight(window.getCOLS());
            }
        }
    
        void CursorMover::moveCursorRightInsertMode(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                cursor.moveRightInsertMode(window.getCOLS());
            }
        }




        void CursorMover::moveToFrontOfLine() {
            document.moveToFrontOfLine();
            cursor.updateNewTriple(document.getTriple());
        }

        void CursorMover::moveToFirstCharOfLine() {
            document.moveToFirstCharOfLine();
            cursor.updateNewTriple(document.getTriple());
        }

        void CursorMover::moveToEndOfLine() {
            document.moveToEndOfLine();
            cursor.updateNewTriple(document.getTriple());
        }



        void CursorMover::moveToNextWord(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                document.moveToNextWord();
            }
            cursor.updateNewTriple(document.getTriple());
        }

        void CursorMover::moveToNextNonWhitespace(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                document.moveToNextNonWhitespace();
            }
            cursor.updateNewTriple(document.getTriple());
        }

        void CursorMover::moveToPrevWord(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                document.moveToPrevWord();
            }
            cursor.updateNewTriple(document.getTriple());
        }

        void CursorMover::moveToPrevNonWhitespace(int multiplier) {
            for (int i = 0; i < multiplier; i++) {
                document.moveToPrevNonWhitespace();
            }
            cursor.updateNewTriple(document.getTriple());
        }

















    
        void CursorMover::updateCursorTriple(const Triple &t) {
            cursor.updateNewTriple(t);
        }

        void CursorMover::updateCursor() {
            cursor.updateNewTriple(document.getTriple());
        }








}