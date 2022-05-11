#include"parser.h"

void Env::put(int ad, char* name){
    std::string tar = std::string(name, strlen(name));
    table[tar]=m_idx;
    m_idx+=ad;
}

int Env::get(char* name){
    std::string tar= std::string(name, strlen(name));
    for(Env e=this; ; e=*(e.prev)){
        if(e.table.find(tar)!=e.table.end()) return e.table.find(tar)->second;
        if(e.prev==(Env*)NULL) break;
    }
    return -1;
}


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
    if((*token_iter)->type==a){
        printf("\nmatch! inner code: %d",(*token_iter)->type); 
        if(a==IDENTIFIER){
            printf("\nmet identifier!! executing...\n");
            if(top->get((*token_iter)->token_buffer)!=-1) printf("found in table!\n");
            else {
                top->put(4, (*token_iter)->token_buffer); 
                printf("number %d loaded in table\n", top->get((*token_iter)->token_buffer));
                }//字节为单位寻址
        }
        go(); 
        return 1;} 
    return 0;
}

int parser::match(enum TokenType a, enum TokenType b){
    if((*token_iter)->type>=a&&(*token_iter)->type<=a){printf("\nmatch! inner code: %d",(*token_iter)->type); go(); return 1;} 
    return 0;
}

int parser::go(){
    token_iter++;
    if(token_iter==tokenlist.end()) return 0;
    return 1;
}

int parser::back(){
    if(token_iter==tokenlist.begin()) return 0;
    token_iter--;
    return 1;
}

void parser::parseError(){
    printf("\nParse Error:");
    printToken(*token_iter);
    printf("\n");
}

int parser::parse(){
    token_iter=tokenlist.begin();
    if(program()){printf("compile success!"); return 1;}
    printf("compile failure!");
    return 0;

}

int parser::program(){
    if(programhead()&&block()&&match(DOT)) return 1;
    return 0;
}
int parser::block(){
    Env *topSave=top;
    top=new Env(topSave);
    
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(constexp()&&varexp()&&prodef()&&compsent()){printf("block matched!!\n");top=topSave; return 1;}
    token_iter=scope_iter;
    top=topSave;
    printf("block unmatched\n");
    return 0;
}
int parser::constdef(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)&&match(O_EQUAL)&&match(INT)) return 1; 
    token_iter=scope_iter;
    return 0;
}
int parser::constsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_COMMA)&&constdef()&&constsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::varsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(vardef()&&varsuff()) return 1;
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
    if(prohead()&&prohead()&&block()&&match(SEMICOLON)&&prosuff()) return 1;
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
    if(match(K_IF)&&condition()&&match(K_THEN)&&sentence()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::whilesent(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_WHILE)&&condition()&&match(K_DO)&&sentence()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::write(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_WRITE)&&match(L_PAREN)&&express()&&exprsuff()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::exprsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_COMMA)&&express()&&exprsuff()) return 1;
    token_iter=scope_iter;
    return 1; 
}
int parser::condition(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(express()&&relationopt()&&express()) return 1;
    token_iter=scope_iter;
    if(match(K_ODD)&&express()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::express(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_ADD)&&term()&&termsuff()) return 1;
    token_iter=scope_iter;
    if(match(O_MUS)&&term()&&termsuff()) return 1;
    token_iter=scope_iter;
    if(term()&&termsuff()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::factorsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(mulopt()&&factor()&&factorsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::factor(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)) return 1;
    token_iter=scope_iter;
    if(match(INT)) return 1;
    token_iter=scope_iter;
    if(match(L_PAREN)&&express()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::mulopt(){
    if(match(O_MUL)||match(O_DIV)) return 1;
    return 0;
}


int parser::programhead(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_PROGRAM)&&match(IDENTIFIER)&&match(SEMICOLON)){printf("\nprogram head matched!\n"); return 1;}
    token_iter=scope_iter;
    return 0;
}
int parser::constexp(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_CONST)&&constdef()&&constsuff()) {return 1;}
    token_iter=scope_iter;
    return 1;
}
int parser::varexp(){
    printf("\nthis is varexp\ncurrent token is %d\n", (*token_iter)->type);
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_VAR)&&vardef()&&varsuff()) {return 1;}
    token_iter=scope_iter;
    return 1;
}
int parser::vardef(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)&&idsuff()&&match(COLON)&&type()&&match(SEMICOLON)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::prodef(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(prohead()&&block()&&match(SEMICOLON)&&prodef()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::prohead(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_PROCEDURE)&&argument()&&match(SEMICOLON)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::assign_or_call(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(IDENTIFIER)&&suffix()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::suffix(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(ASSIGN)&&express()) return 1;
    token_iter=scope_iter;
    if(match(L_PAREN)&&express()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::read(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_READ)&&match(L_PAREN)&&match(IDENTIFIER)&&idsuff()&&match(R_PAREN)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::idsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(O_COMMA)&&match(IDENTIFIER)&&idsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::compsent(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(K_BEGIN)&&sentence()&&sentsuff()&&match(K_END)) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::sentsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(SEMICOLON)&&sentence()&&sentsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::termsuff(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(addopt()&&term()&&termsuff()) return 1;
    token_iter=scope_iter;
    return 1;
}
int parser::term(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(factor()&&factorsuff()) return 1;
    token_iter=scope_iter;
    return 0;
}
int parser::argument(){
    std::list<struct Token*>::iterator scope_iter=token_iter;
    if(match(L_PAREN)&&match(IDENTIFIER)&&match(COLON)&&type()&&match(R_PAREN)) return 1;
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
    myparser->parse();
}