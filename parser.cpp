#include"parser.h"
#include<string.h>
#include<stack>

using std::cout;
using std::endl;

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

/*--------------------this section for predict mode----------------*/

int parser::predict_parser(){

    token_iter=tokenlist.begin();
    TABLE_STACK.push(256);
    TABLE_STACK.push(128);

    error=0;
    while(!TABLE_STACK.empty()&&!error){
        cout<<"current top:"<<TABLE_STACK.top()<<" current token:"<<(*token_iter)->type<<endl;
        maintain_predict_stack(TABLE_STACK.top(), (int)(*token_iter)->type);

        if(TABLE_STACK.top()==256&&token_iter==tokenlist.end()){
            cout<<"current top:"<<TABLE_STACK.top()<<" current token:"<<256<<endl;
            cout<<"compile success"<<endl;
            break;
        }
    }
    return 0;
}

void parser::maintain_predict_stack(int nondet, int token){
    if(nondet==128){
        if(token==1){
            TABLE_STACK.pop();
            TABLE_STACK.push(27);//right to left
            TABLE_STACK.push(130);
            TABLE_STACK.push(129);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==129){
        if(token==1){
            TABLE_STACK.pop();
            TABLE_STACK.push(28);//right to left
            TABLE_STACK.push(34);
            TABLE_STACK.push(1);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==130){
        if(token==2||token==3||token==6||token==13||token==28){
            TABLE_STACK.pop();
            TABLE_STACK.push(149);//right to left
            TABLE_STACK.push(137);
            TABLE_STACK.push(133);
            TABLE_STACK.push(131);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==131){
        if(token==2){
            TABLE_STACK.pop();
            TABLE_STACK.push(134);//right to left
            TABLE_STACK.push(132);
            TABLE_STACK.push(2);
        }
        else if(token==3||token==256){
            TABLE_STACK.pop();//met epsilon
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==132){
        if(token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(33);//right to left
            TABLE_STACK.push(20);
            TABLE_STACK.push(34);//right to left
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==133){
        if(token==3){
            TABLE_STACK.pop();
            TABLE_STACK.push(136);//right to left
            TABLE_STACK.push(135);
            TABLE_STACK.push(3);//right to left
        }
        else if(token==2||token==6||token==28||token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==134){
        if(token==26){
            TABLE_STACK.pop();
            TABLE_STACK.push(134);//right to left
            TABLE_STACK.push(132);
            TABLE_STACK.push(26);//right to left
        }
        else if(token==3||token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==135){
        if(token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(28);//right to left
            TABLE_STACK.push(138);
            TABLE_STACK.push(29);//right to left
            TABLE_STACK.push(147);//right to left
            TABLE_STACK.push(34);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==136){
        if(token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(136);//right to left
            TABLE_STACK.push(135);
        }
        else if(token==2||token==6||token==28||token==256||token==13){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==137){
        if(token==6){
            TABLE_STACK.pop();
            TABLE_STACK.push(140);//right to left
            TABLE_STACK.push(28);
            TABLE_STACK.push(130);
            TABLE_STACK.push(39);
        }
        else if(token==13||token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==138){
        if(token==5){
            TABLE_STACK.pop();
            TABLE_STACK.push(5);//right to left
        }
        else if(token==4){
            TABLE_STACK.pop();
            TABLE_STACK.push(4);//right to left
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==139){
        if(token==6){
            TABLE_STACK.pop();
            TABLE_STACK.push(28);
            TABLE_STACK.push(157);
            TABLE_STACK.push(6);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==140){
        if(token==6){
            TABLE_STACK.pop();
            TABLE_STACK.push(140);//right to left
            TABLE_STACK.push(28);
            TABLE_STACK.push(130);
            TABLE_STACK.push(39);
        }
        else if(token==13||token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==141){
        if(token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(143);
            TABLE_STACK.push(34);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==142){
        if(token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(141);
        }
        else if(token==7){
            TABLE_STACK.pop();
            TABLE_STACK.push(144);
        }
        else if(token==9){
            TABLE_STACK.pop();
            TABLE_STACK.push(146);
        }
        else if(token==11){
            TABLE_STACK.pop();
            TABLE_STACK.push(145);
        }
        else if(token==12){
            TABLE_STACK.pop();
            TABLE_STACK.push(148);
        }
        else if(token==13){
            TABLE_STACK.pop();
            TABLE_STACK.push(149);
        }
        else if(token==28||token==256||token==14){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==143){
        if(token==30){
            TABLE_STACK.pop();
            TABLE_STACK.push(154);
            TABLE_STACK.push(30);//right to left
        }
        else if(token==31){
            TABLE_STACK.pop();
            TABLE_STACK.push(32);
            TABLE_STACK.push(154);//right to left
            TABLE_STACK.push(31);
        }
        else if(token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==144){
        if(token==7){
            TABLE_STACK.pop();
            TABLE_STACK.push(142);
            TABLE_STACK.push(8);//right to left
            TABLE_STACK.push(152);
            TABLE_STACK.push(7);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==145){
        if(token==11){
            TABLE_STACK.pop();
            TABLE_STACK.push(32);
            TABLE_STACK.push(147);//right to left
            TABLE_STACK.push(34);
            TABLE_STACK.push(31);
            TABLE_STACK.push(11);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==146){
        if(token==9){
            TABLE_STACK.pop();
            TABLE_STACK.push(142);
            TABLE_STACK.push(10);//right to left
            TABLE_STACK.push(152);
            TABLE_STACK.push(9);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==147){
        if(token==26){
            TABLE_STACK.pop();
            TABLE_STACK.push(147);
            TABLE_STACK.push(34);//right to left
            TABLE_STACK.push(26);
        }
        else if(token==29||32){
            TABLE_STACK.pop();
        }
        else if(token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==148){
        if(token==12){
            TABLE_STACK.pop();
            TABLE_STACK.push(32);
            TABLE_STACK.push(150);//right to left
            TABLE_STACK.push(154);
            TABLE_STACK.push(31);
            TABLE_STACK.push(12);//right to left
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==149){
        if(token==13){
            TABLE_STACK.pop();
            TABLE_STACK.push(14);
            TABLE_STACK.push(151);//right to left
            TABLE_STACK.push(142);
            TABLE_STACK.push(13);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==150){
        if(token==26){
            TABLE_STACK.pop();
            TABLE_STACK.push(150);
            TABLE_STACK.push(154);//right to left
            TABLE_STACK.push(26);
        }
        else if(token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==151){
        if(token==28){
            TABLE_STACK.pop();
            TABLE_STACK.push(151);
            TABLE_STACK.push(142);//right to left
            TABLE_STACK.push(28);
        }
        else if(token==256||token==14){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==152){
        if(token==16){
            TABLE_STACK.pop();
            TABLE_STACK.push(154);
            TABLE_STACK.push(161);//right to left
            TABLE_STACK.push(154);
        }
        else if(token==15){
            TABLE_STACK.pop();
            TABLE_STACK.push(154);
            TABLE_STACK.push(15);//right to left
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==153){
        if(token==16){
            TABLE_STACK.pop();
            TABLE_STACK.push(153);
            TABLE_STACK.push(155);//right to left
            TABLE_STACK.push(159);
        }
        else if(token==256||token==32||token==20||token==26||token==28){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==154){
        if(token==16){
            TABLE_STACK.pop();
            TABLE_STACK.push(153);
            TABLE_STACK.push(155);//right to left
            TABLE_STACK.push(16);
        }
        else if(token==17){
            TABLE_STACK.pop();
            TABLE_STACK.push(153);
            TABLE_STACK.push(155);//right to left
            TABLE_STACK.push(17);
        }
        else if(token==33){
            TABLE_STACK.pop();
            TABLE_STACK.push(153);
            TABLE_STACK.push(155);//right to left
        }
        else if(token==18||token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(153);
            TABLE_STACK.push(155);//right to left
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==155){
        if(token==34||33){
            TABLE_STACK.pop();
            TABLE_STACK.push(156);
            TABLE_STACK.push(158);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==156){
        if(token==18){
            TABLE_STACK.pop();
            TABLE_STACK.push(156);
            TABLE_STACK.push(158);//right to left
            TABLE_STACK.push(160);
        }
        else if(token==256||token==8||token==10||token==14||token==16||token==18||token==20||token==26||token==28||token==32||token==34){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==157){
        if(token==31){
            TABLE_STACK.pop();
            TABLE_STACK.push(32);
            TABLE_STACK.push(138);//right to left
            TABLE_STACK.push(29);
            TABLE_STACK.push(34);
            TABLE_STACK.push(31);
        }
        else if(token==256){
            TABLE_STACK.pop();
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==158){
        if(token==34){
            TABLE_STACK.pop();
            TABLE_STACK.push(34);
        }
        else if(token==33){
            TABLE_STACK.pop();
            TABLE_STACK.push(33);
        }
        else if(token==31){
            TABLE_STACK.pop();
            TABLE_STACK.push(32);
            TABLE_STACK.push(154);
            TABLE_STACK.push(31);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==159){
        if(token==16){
            TABLE_STACK.pop();
            TABLE_STACK.push(16);
        }
        else if(token==17){
            TABLE_STACK.pop();
            TABLE_STACK.push(17);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==160){
        if(token==18){
            TABLE_STACK.pop();
            TABLE_STACK.push(18);
        }
        else if(token==19){
            TABLE_STACK.pop();
            TABLE_STACK.push(19);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet==161){
        if(token>=20&&token<=25){
            TABLE_STACK.pop();
            TABLE_STACK.push(token);
        }
        else{cout<<"parser error!"<<endl; error=1;}
    }
    else if(nondet<100){//is det
        if(token_iter!=tokenlist.end()) token_iter++;
        TABLE_STACK.pop();
    }
    else if(nondet==256) return;
}

/*--------------------this section for predict mode----------------*/

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



int main(int argc, char** argv){

    struct parser *myparser = new struct parser;
    myparser->initParser("test.pas");
    if(argc>1){
        if(strcmp(argv[1], "-r")==0) myparser->parse();
        if(strcmp(argv[1], "-p")==0) myparser->predict_parser();
    }
    else myparser->predict_parser();
}