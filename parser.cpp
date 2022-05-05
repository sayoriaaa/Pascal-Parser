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
    return 0;
}
int parser::whilesent(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_WHILE)&&go()&&condition()&&go()&&match(K_DO)&&go()&&sentence()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::write(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_WRITE)&&go()&&match(L_PAREN)&&go()&&express()&&go()&&exprsuff()&&go()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::exprsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_COMMA)&&go()&&express()&&go()&&exprsuff()) return 1;
    token_iter=scope_iter;
    return 1; 
}
int parser::condition(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(express()&&go()&&relationopt()&&go()&&express()) return 1;
    token_iter=scope_iter;
    if(match(K_ODD)&&go()&&express()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::express(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_ADD)&&go()&&term()&&go()&&termsuff()) return 1;
    token_iter=scope_iter;
    if(match(O_MUS)&&go()&&term()&&go()&&termsuff()) return 1;
    token_iter=scope_iter;
    if(term()&&go()&&termsuff()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::factorsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(mulopt()&&go()&&factor()&&go()&&factorsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::factor(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)) return 1;
    token_iter=scope_iter;
    if(match(INT)) return 1;
    token_iter=scope_iter;
    if(match(L_PAREN)&&go()&&express()&&go()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::mulopt(){
    if(match(O_MUL)||match(O_DIV)) return 1;
    return 0;
}


int parser::programhead(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_PROGRAM)&&go()&&match(IDENTIFIER)&&go()&&match(SEMICOLON)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::constexp(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_CONST)&&go()&&constdef()&&go()&&constsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::varexp(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_VAR)&&go()&&vardef()&&go()&&varsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::vardef(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)&&go()&&idsuff()&&go()&&match(COLON)&&go()&&type()&&go()&&match(SEMICOLON)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::prodef(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(prohead()&&go()&&block()&&go()&&match(SEMICOLON)&&go()&&prodef()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::prohead(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_PROCEDURE)&&go()&&argument()&&go()&&match(SEMICOLON)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::assign_or_call(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)&&go()&&suffix()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::suffix(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(ASSIGN)&&go()&&express()) return 1;
    token_iter=scope_iter;
    if(match(L_PAREN)&&go()&&express()&&go()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::read(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_READ)&&go()&&match(L_PAREN)&&go()&&match(IDENTIFIER)&&go()&&idsuff()&&go()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::idsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_COMMA)&&go()&&match(IDENTIFIER)&&go()&&idsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::compsent(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_BEGIN)&&go()&&sentence()&&go()&&sentsuff()&&go()&&match(K_END)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::sentsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(SEMICOLON)&&go()&&sentence()&&go()&&sentsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::termsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(addopt()&&go()&&term()&&go()&&termsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::term(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(factor()&&go()&&factorsuff()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::argument(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(L_PAREN)&&go()&&match(IDENTIFIER)&&go()&&match(COLON)&&go()&&type()&&go()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::addopt(){
    if(match(O_ADD)||match(O_MUS)) return 1;
    return 0;
}
int parser::relationopt(){
    if(match(O_EQUAL, O_GREATER_EQUAL)) return 1;
    return 0;
}



int main(){
    struct parser *myparser = new struct parser;
    myparser->initParser("test.pas");
}