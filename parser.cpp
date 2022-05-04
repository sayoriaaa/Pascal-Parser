#include"parser.h"

void parser::initParser(const char* s_filename){
    struct Lexer *mylexer=new struct Lexer;
    mylexer->InitSourceCode(s_filename);
    struct Token *ctoken=mylexer->GetNextToken();
    while(1){
        printToken(ctoken);
        ctoken=mylexer->GetNextToken();
        if(mylexer->reach_end==1){
            printToken(ctoken);
            break;          
        }
    }    
}

int main(){
    struct parser *myparser = new struct parser;
    myparser->initParser("test.pas");
}