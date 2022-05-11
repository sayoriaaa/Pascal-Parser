#ifndef PARSER_H
#define PARSER_H
#include"lexer.h"
#include<list>
#include<map>
#include<iostream>
#include<string>

class Env{     
    protected:
        Env *prev;
    public:
        int m_idx;
        std::map<std::string, int> table;
        Env(Env *p){prev=p;m_idx=0;}
        void put(int ad, char* name);
        int get(char* name);
};

struct parser{
    int error=0;
    Env *top=new Env((Env*)NULL);

    std::list<struct Token*> tokenlist;
    std::list<struct Token*>::iterator token_iter;

    void initParser(const char* s_filename);
    int parse();
    int match(enum TokenType a, enum TokenType b);
    int match(enum TokenType a);
    int go();
    int back();
    void parseError();
    

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

    int programhead();
    int constexp();
    int varexp();
    int vardef();
    int prodef();
    int prohead();
    int assign_or_call();
    int suffix();
    int read();
    int idsuff();
    int compsent();
    int sentsuff();
    int termsuff();
    int term();
    int argument();
    int addopt();
    int relationopt();
};

#endif
