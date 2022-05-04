#include"lexer.h"

void Lexer::InitSourceCode(const char* filename){//initialize
    
    FILE *f=fopen(filename, "rb");
    if(f==NULL) printf("file not exist!\n");
    else{
        CurrentBuffer=new char[BUFFER_SIZE+1];
        NextBuffer=new char[BUFFER_SIZE+1];

        CurrentBuffer_len=fread(CurrentBuffer, 1, BUFFER_SIZE, f);
        if(CurrentBuffer_len<BUFFER_SIZE) NextBuffer[0]='\0';
        else NextBuffer_len=fread(NextBuffer, 1, BUFFER_SIZE, f);

        CurrentBuffer[CurrentBuffer_len]='\0';
        NextBuffer[NextBuffer_len]='\0';

        //printf("CurrentBuffer:%s\nlen:%d\nNextBuffer:%s\nlen:%d\n",CurrentBuffer,CurrentBuffer_len,NextBuffer,NextBuffer_len);

        forward=CurrentBuffer;
        lexemeBegin=CurrentBuffer;
        currentF=f;
    }
}

char Lexer::GetNextChar(){//返回0说明到达文件末尾
    if(*forward=='\0'){
        if(forward_num==BUFFER_SIZE){//仅当最后一位是'\0'时才可以加载NextBuffer
            forward_num=0;
            forward=NextBuffer;
            switch_buffer=1;
        }
        if(*forward=='\0'&&forward_num<BUFFER_SIZE){reach_end=1; return '\0';};//检测了移到新的缓存的情况，可以继续往下走
    }
    NextChar=*forward;
    if(NextChar=='\n'){line++;column=0;}
    forward++;
    forward_num++; 
    column++;
    return NextChar;  
}

struct Token* Lexer::GetNextToken(){
    if(switch_buffer){
        strcpy(CurrentBuffer,NextBuffer);
        CurrentBuffer_len=NextBuffer_len;

        if(NextBuffer_len==BUFFER_SIZE){//当前的BUFFER又是满的
            NextBuffer_len=fread(NextBuffer, 1, BUFFER_SIZE, currentF);
            NextBuffer[NextBuffer_len]='\0';
            //printf("CurrentBuffer:%s\nlen:%d\nNextBuffer:%s\nlen:%d\n",CurrentBuffer,CurrentBuffer_len,NextBuffer,NextBuffer_len);
        }
        forward=&CurrentBuffer[forward_num];
    }
    switch_buffer=0;

    struct Token *ret = new struct Token;
    ret->scan(this);
    ret->line=line;
    ret->column=column;

    token_num++;
    lexemeBegin=forward;   
    return ret;
}

char Lexer::peek(int num){//for forward
    if(num+forward_num<BUFFER_SIZE) return CurrentBuffer[num+forward_num<BUFFER_SIZE];
    return NextBuffer[num+forward_num-BUFFER_SIZE];
}

void Token::scan(struct Lexer *mylexer){//留下再前进一位的forward
    if(mylexer->token_num==0) mylexer->GetNextChar();
    char currentChar=mylexer->NextChar;//这里相当于forward指针回退,用了已经保存的前一个

    while(isspace(currentChar)) currentChar=mylexer->GetNextChar();//去除先导无用符号
    
    if(isdigit(currentChar)){//handle integer
        type=INT;
        token_buffer[token_buffer_len++]=currentChar;
        currentChar=mylexer->GetNextChar();      
        while(isdigit(currentChar)){
            token_buffer[token_buffer_len++]=currentChar;
            currentChar=mylexer->GetNextChar();
        }
        token_buffer[token_buffer_len]='\0';
        int_val=atoi(token_buffer);
        return;
    }
    else if(isalpha(currentChar)){//handle keyword and identifier
        token_buffer[token_buffer_len++]=tolower(currentChar);
        currentChar=mylexer->GetNextChar();
        while(isalnum(currentChar)){
            token_buffer[token_buffer_len++]=tolower(currentChar);//PASCAL大小写不敏感！
            currentChar=mylexer->GetNextChar();
        }
        token_buffer[token_buffer_len]='\0';

        if(strcmp(token_buffer, "program")==0) type=K_PROGRAM;
        else if(strcmp(token_buffer, "const")==0) type=K_CONST;
        else if(strcmp(token_buffer, "var")==0) type=K_VAR;
        else if(strcmp(token_buffer, "integer")==0) type=K_INTEGER;
        else if(strcmp(token_buffer, "long")==0) type=K_LONG;
        else if(strcmp(token_buffer, "procedure")==0) type=K_PROCEDURE;
        else if(strcmp(token_buffer, "if")==0) type=K_IF;
        else if(strcmp(token_buffer, "then")==0) type=K_THEN;
        else if(strcmp(token_buffer, "while")==0) type=K_WHILE;
        else if(strcmp(token_buffer, "do")==0) type=K_DO;
        else if(strcmp(token_buffer, "read")==0) type=K_READ;
        else if(strcmp(token_buffer, "write")==0) type=K_WRITE;
        else if(strcmp(token_buffer, "begin")==0) type=K_BEGIN;
        else if(strcmp(token_buffer, "end")==0) type=K_END;
        else if(strcmp(token_buffer, "odd")==0) type=K_ODD;
        else type=IDENTIFIER;
    }
    else{
        if(currentChar=='<'){
            currentChar=mylexer->GetNextChar();
            if(currentChar=='>'){type=O_NOT_EQUAL; mylexer->GetNextChar();} 
            else if(currentChar=='='){type=O_LESS_EQUAL; mylexer->GetNextChar();}
            else type=O_LESS;
        }
        else if(currentChar=='>'){
            currentChar=mylexer->GetNextChar();
            if(currentChar=='='){type=O_GREATER_EQUAL; mylexer->GetNextChar();}
            else type=O_GREATER;
        }
        else if(currentChar=='+'){type=O_ADD; mylexer->GetNextChar();}
        else if(currentChar=='-'){type=O_MUS; mylexer->GetNextChar();}
        else if(currentChar=='*'){type=O_MUL; mylexer->GetNextChar();}
        else if(currentChar=='/'){type=O_DIV; mylexer->GetNextChar();}
        else if(currentChar=='.'){type=DOT; mylexer->GetNextChar();}
        else if(currentChar==','){type=O_COMMA; mylexer->GetNextChar();}
        else if(currentChar==';'){type=SEMICOLON; mylexer->GetNextChar();}
        else if(currentChar==':'){
            currentChar=mylexer->GetNextChar();
            if(currentChar=='='){type=ASSIGN; mylexer->GetNextChar();}
            else type=COLON;
        }
        else if(currentChar=='='){type=O_EQUAL; mylexer->GetNextChar();}
        else if(currentChar=='('){type=L_PAREN; mylexer->GetNextChar();}
        else if(currentChar==')'){type=R_PAREN; mylexer->GetNextChar();}
        else if(currentChar=='#'){type=SHARP; mylexer->GetNextChar();}//记得加上异常处理
    }
}

void printToken(struct Token* ctoken){
    printf("type:%d ", ctoken->type);
    if(ctoken->type==IDENTIFIER) printf("%s ", ctoken->token_buffer);
    if(ctoken->type==INT) printf("%d ", ctoken->int_val);
    printf(" %d:%d ", ctoken->line, ctoken->column);
    printf("\n");
}


