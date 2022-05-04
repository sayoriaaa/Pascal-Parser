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

int parser::match(enum TokenType a){
    if((*token_iter)->type==a) return 1;
    return 0;
}

int parser::match(enum TokenType a, enum TokenType b){
    if((*token_iter)->type>=a&&(*token_iter)->type<=a) return 1;
    return 0;
}

int parser::go(){
    token_iter++;
    if(token_iter==tokenlist.end()) return 0;
    return 1;
}

void parser::parseError(){
    printf("\nParse Error:");
    printToken(*token_iter);
    printf("\n");
}

int parser::parse(){
    token_iter=tokenlist.begin();

}

int parser::program(){
    if(programhead()&&go()&&block()&&go()&&match(DOT)) return 1;
    return 0;
}
int parser::block(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(constexp()&&go()&&varexp()&&go()&&prodef()&&go()&&compsent()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::constdef(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)&&go()&&match(O_EQUAL)&&go()&&match(INT)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::constsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_COMMA)&&go()&&constdef()&&go()&&constsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::varsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(vardef()&&go()&&varsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::type(){
    if(match(K_INTEGER)) return 1;
    if(match(K_LONG)) return 1;
    return 0;
}
int parser::prosuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(prohead()&&go()&&prohead()&&go()&&block()&&go()&&match(SEMICOLON)&&go()&&prosuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::sentence(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(assign_or_call()) return 1;
    token_iter=scope_iter;
    if(ifsent()) return 1;
    token_iter=scope_iter;
    if(whilesent()) return 1;
    token_iter=scope_iter;
    if(read()) return 1;
    token_iter=scope_iter;
    if(write()) return 1;
    token_iter=scope_iter;
    if(compsent()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::ifsent(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_IF)&&go()&&condition()&&go()&&match(K_THEN)&&go()&&sentence()) return 1;
    token_iter=scope_iter;
    retrun 0;
}
int parser::whilesent(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_WHILE)&&go()&&condition()&&go()&&match(K_DO)&&go()&&sentence()) return 1;
    token_iter=scope_iter;
    retrun 0;
}
int parser::write(){

}
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::
void parser::

int main(){
    struct parser *myparser = new struct parser;
    myparser->initParser("test.pas");
}