#ifndef PARSER_H
#define PARSER_H
#include"lexer.h"
#include<list>
#include<iostream>

struct parser{
    int error=0;
    std::list<struct Token*> tokenlist;
    std::list<struct Token*>::iterator token_iter;

    void initParser(const char* s_filename);
    int parse();

    int program();
    int block();
    int constdef();
    int constsuff();
    int varsuff();
    int type();
    int prosuff();
    int sentence();
    int ifsent();
    int whilesent();
    int write();
    int exprsuff();
    int condition();
    int express();
    int factorsuff();
    int factor();
    int mulopt();

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
};

#endif
