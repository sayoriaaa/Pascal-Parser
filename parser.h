#ifndef PARSER_H
#define PARSER_H
#include"lexer.h"

void program();
void block();
void constdef();
void constsuff();
void varsuff();
void type();
void prosuff();
void sentence();
void ifsent();
void whilesent();
void write();
void exprsuff();
void condition();
void express();
void factorsuff();
void factor();
void mulopt();

void programhead();
void constexp();
void varexp();
void vardef();
void prodef();
void prohead();
void assign_or_call();
void suffix();
void read();
void idsuff();
void compsent();
void sentsuff();
void termsuff();
void term();
void argument();
void addopt();
void relationopt();








struct parser{
    static int error;

    void initParser(const char* s_filename);
};

#endif
