#include"parser.h"

void parser::initParser(const char* s_filename){
    struct Lexer *mylexer=new struct Lexer;
    mylexer->InitSourceCode(s_filename);
    struct Token *ctoken=mylexer->GetNextToken();
    while(1){
        tokenlist.push_back(ctoken);
        ctoken=mylexer->GetNextToken();
        if(mylexer->reach_end==1){
            tokenlist.push_back(ctoken);
            break;          
        }
    }
    for(token_iter=tokenlist.begin();token_iter!=tokenlist.end();token_iter++) printToken(*token_iter);     
}

int main(){
    struct parser *myparser = new struct parser;
    myparser->initParser("test.pas");
}