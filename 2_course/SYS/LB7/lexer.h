#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
class tLexer :public tBaseLexer {
public:
    tLexer() :tBaseLexer() {
        // вещественное
        Adec.add(0, '+', 1);
        Adec.add(0, '-', 1);
        addrange(Adec, 1, '0', '9', 2);
        addrange(Adec, 2, '0', '9', 2);

        Adec.add(1, '.', 3);
        Adec.add(2, '.', 3);

        addrange(Adec, 3, '0', '9', 4);
        addrange(Adec, 4, '0', '9', 4);

        Adec.add(4, 'e', 5);
        Adec.add(4, 'E', 5);

        Adec.add(5, '+', 6);
        Adec.add(5, '-', 6);

        addrange(Adec, 6, '0', '9', 7);
        addrange(Adec, 7, '0', '9', 7);
        addrange(Adec, 5, '0', '9', 7);

        Adec.final(7);
        //________________________________________

        // id
        //--?

        addstr(Aid, 0, "!", 1);
        addrange(Aid, 0, 'A', 'Z', 1);
        addrange(Aid, 0, 'a', 'z', 1);
        addstr(Aid, 0, "?", 2);

        addrange(Aid, 1, 'A', 'Z', 1);
        addrange(Aid, 1, 'a', 'z', 1);
        addrange(Aid, 1, '0', '9', 1);
        addstr(Aid, 1, "!", 1);
        addstr(Aid, 1, "?", 2);
        addstr(Aid, 1, "-", 3);

        addrange(Aid, 2, 'A', 'Z', 1);
        addrange(Aid, 2, 'a', 'z', 1);
        addrange(Aid, 2, '0', '9', 1);
        addstr(Aid, 2, "!", 1);
        addstr(Aid, 2, "?", 2);
        addstr(Aid, 2, "-", 3);

        addstr(Aid, 3, "?", 2);
        addstr(Aid, 3, "-", 4);
        addrange(Aid, 3, 'A', 'Z', 1);
        addrange(Aid, 3, 'a', 'z', 1);
        addrange(Aid, 3, '0', '9', 1);
        addstr(Aid, 3, "!", 1);

        addstr(Aid, 4, "?", 5);
        addstr(Aid, 4, "-", 4);
        addrange(Aid, 4, 'A', 'Z', 1);
        addrange(Aid, 4, 'a', 'z', 1);
        addrange(Aid, 4, '0', '9', 1);
        addstr(Aid, 4, "!", 1);

        addstr(Aid, 5, "?", 5);
        addstr(Aid, 5, "-", 5);
        addrange(Aid, 5, 'A', 'Z', 5);
        addrange(Aid, 5, 'a', 'z', 5);
        addrange(Aid, 5, '0', '9', 5);
        addstr(Aid, 5, "!", 5);

        Aid.final(1);


        // idq
        // !?

        addstr(Aidq, 0, "?", 2);
        addstr(Aidq, 0, "-", 1);
        addrange(Aidq, 0, 'A', 'Z', 1);
        addrange(Aidq, 0, 'a', 'z', 1);
        addstr(Aidq, 0, "!", 3);

        addrange(Aidq, 1, 'A', 'Z', 1);
        addrange(Aidq, 1, 'a', 'z', 1);
        addrange(Aidq, 1, '0', '9', 1);
        addstr(Aidq, 1, "!", 3);
        addstr(Aidq, 1, "-", 1);
        addstr(Aidq, 1, "?", 2);

        addstr(Aidq, 2, "?", 2);
        addstr(Aidq, 2, "-", 1);
        addrange(Aidq, 2, 'A', 'Z', 1);
        addrange(Aidq, 2, 'a', 'z', 1);
        addrange(Aidq, 2, '0', '1', 1);
        addstr(Aidq, 2, "!", 3);

        addstr(Aidq, 3, "?", 4);
        addstr(Aidq, 3, "-", 1);
        addrange(Aidq, 3, 'A', 'Z', 1);
        addrange(Aidq, 3, 'a', 'z', 1);
        addrange(Aidq, 3, '0', '9', 1);
        addstr(Aidq, 3, "!", 3);

        addstr(Aidq, 4, "?", 4);
        addstr(Aidq, 4, "-", 4);
        addrange(Aidq, 4, 'A', 'Z', 4);
        addrange(Aidq, 4, 'a', 'z', 4);
        addrange(Aidq, 4, '0', '9', 4);
        addstr(Aidq, 4, "!", 4);

        Aidq.final(2);
    }
};
#endif