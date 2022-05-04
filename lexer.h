#ifndef LEXER_H
#define LEXER_H

#define BUFFER_SIZE 4096
#define TOKEN_BUFFER 256

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

enum TokenType{
    K_PROGRAM=1,
    K_CONST,
    K_VAR,
    K_INTEGER,
    K_LONG,
    K_PROCEDURE,
    K_IF,
    K_THEN,
    K_WHILE,
    K_DO,
    K_READ,
    K_WRITE,
    K_BEGIN,
    K_END,
    K_ODD,

    O_ADD,
    O_MUS,
    O_MUL,
    O_DIV,
    O_EQUAL,
    O_NOT_EQUAL,
    O_LESS,
    O_LESS_EQUAL,
    O_GREATER,
    O_GREATER_EQUAL,
    O_COMMA,

    DOT,
    SEMICOLON,
    COLON,
    ASSIGN,
    L_PAREN,
    R_PAREN,
    INT,
    IDENTIFIER,
    SHARP
};

struct Token{
    char token_buffer[TOKEN_BUFFER];//use to identify type(如果是IDENTIFIER则为名称)
    int token_buffer_len=0;
    int line=0, column=0;
    enum TokenType type;
    int int_val;

    void scan(struct Lexer* mylexer);//get token_buffer
};




struct Lexer{
    int reach_end=0;
    FILE *currentF;
    char NextChar;
    char *CurrentBuffer=NULL, *NextBuffer=NULL;
    int NextBuffer_len=0, CurrentBuffer_len=0;;//记录下一个缓冲区大小，为后面交替使用
    char *forward=NULL, *lexemeBegin=NULL;
    int line=0, column=0;
    int forward_num=0, token_num=0;//记录缓冲区forward下标
    int switch_buffer=0;//标记是否需要加载新的BUFFER

    void InitSourceCode(const char* filename);
    char peek(int num);
    char GetNextChar();
    struct Token *GetNextToken();
};

void printToken(struct Token* ctoken);


#endif