
#include <vector>
#include <iostream>
#include <set>

using namespace std;

#define epsilon 0
#define program 128
#define programhead 129
#define block 130
#define constexp 131
#define constdef 132
#define varexp 133
#define constsuff 134
#define vardef 135
#define varsuff 136
#define prodef 137
#define type 138
#define prohead 139
#define prosuff 140
#define assign_or_call 141
#define sentence 142
#define suffix 143
#define ifsent 144
#define read 145
#define whilesent 146
#define idsuff 147
#define write 148
#define compsent 149
#define exprsuff 150
#define sentsuff 151
#define condition 152
#define termsuff 153
#define express 154
#define term 155
#define factorsuff 156
#define argument 157
#define factor 158
#define addopt 159
#define mulopt 160
#define relationopt 161

#define K_PROGRAM 1
#define K_CONST 2
#define K_VAR 3
#define K_INTEGER 4
#define K_LONG 5
#define K_PROCEDURE 6
#define K_IF 7
#define K_THEN 8
#define K_WHILE 9
#define K_DO 10
#define K_READ 11
#define K_WRITE 12
#define K_BEGIN 13
#define K_END 14
#define K_ODD 15

#define O_ADD 16
#define O_MUS 17
#define O_MUL 18
#define O_DIV 19
#define O_EQUAL 20
#define O_NOT_EQUAL 21
#define O_LESS 22
#define O_LESS_EQUAL 23
#define O_GREATER 24
#define O_GREATER_EQUAL 25
#define O_COMMA 26

#define DOT 27
#define SEMICOLON 28
#define COLON 29
#define ASSIGN 30
#define L_PAREN 31
#define R_PAREN 32
#define INT 33
#define IDENTIFIER 34
#define SHARP 35

#define FSHARP 256//to mark FOLLOW SET


void get_first(int pro, vector<vector<vector<int> > > &PRODUCTION, vector<set<int> > &FIRST_SET){
    if(pro>100) pro-=128;//fix bug

    if(FIRST_SET[pro].size()>0) return;
    int exist_epsilon=0;
    int epsilon_num=0;
    if(PRODUCTION[pro].back()[0]==0) exist_epsilon=1;
    //cout<<pro+128<<" "<<exist_epsilon<<endl;

    for(int i=0; i<PRODUCTION[pro].size()-exist_epsilon; i++){//choose production
        if(PRODUCTION[pro][i][0]<100){
            FIRST_SET[pro].insert(PRODUCTION[pro][i][0]);// first one is det
            break;
        }
        else{
            for(int j=0; j<PRODUCTION[pro][i].size(); j++){
                if(PRODUCTION[pro][i][j]<100){
                    FIRST_SET[pro].insert(PRODUCTION[pro][i][j]);//met det in middle; break
                    break;
                }
                int seek_pro=PRODUCTION[pro][i][j]-128;// as above
                get_first(seek_pro, PRODUCTION, FIRST_SET);
                for(auto x=FIRST_SET[seek_pro].begin(); x!=FIRST_SET[seek_pro].end(); x++){//copy FIRST(seek_pro)-epsilon to FIRST(pro)
                    if((*x)==epsilon) continue;
                    FIRST_SET[pro].insert(*x);
                    //cout<<"copy:"<<*x<<endl;
                }
                if(FIRST_SET[seek_pro].find(epsilon)==FIRST_SET[seek_pro].end()) epsilon_num++;
                else break;
            }
            if(epsilon_num==PRODUCTION[pro][i].size()) exist_epsilon=1;//produce epsilon indirectly
        }
    }
    if(exist_epsilon) FIRST_SET[pro].insert(epsilon);

    if(FIRST_SET[pro].size()==0) FIRST_SET[pro].insert(-1);//if error
    //cout<<pro+128<<" calculated!"<<endl;
    return;
}

void get_follow(vector<vector<vector<int> > > &PRODUCTION, vector<set<int> > &FIRST_SET, vector<set<int> > &FOLLOW_SET){
    int refresh=1;
    int exist_epsilon=0;
    
    while(refresh){
        refresh=0;
        for(int i=0; i<FOLLOW_SET.size(); i++){
            if(PRODUCTION[i].back()[0]==0) exist_epsilon=1;
            for(int j=0; j<PRODUCTION[i].size()-exist_epsilon; j++){
                for(int k=0; k<PRODUCTION[i][j].size(); k++){
                    int curr=PRODUCTION[i][j][k];
                    if(curr>100){//met not det
                        int tmp=FOLLOW_SET[curr-128].size();
                        if(k<PRODUCTION[i][j].size()-1){//&&not last one
                            int curr_next=PRODUCTION[i][j][k+1];//get next one
                            if(curr_next<100){//next one is det
                                FOLLOW_SET[curr-128].insert(curr_next);
                            }
                            else{//next one also not det
                                int have_epsilon=0;
                                for(auto x=FIRST_SET[curr_next-128].begin(); x!=FIRST_SET[curr_next-128].end(); x++){
                                    if((*x)==epsilon){//epsilon detected
                                        have_epsilon=0;
                                        continue;
                                    }
                                    FOLLOW_SET[curr-128].insert(*x);
                                }//copy FIRST(NEXT) TO FOLLOW(CURRENT) except epsilon
                                if(have_epsilon){
                                    for(auto x=FOLLOW_SET[curr_next-128].begin(); x!=FOLLOW_SET[curr_next-128].end(); x++){
                                        FOLLOW_SET[curr-128].insert(*x);
                                    }//copy FOLLOW(NEXT) TO FOLLOW(CURRENT) except epsilon
                                }         
                            }

                        }
                        else{//is the last one
                            for(auto x=FOLLOW_SET[i].begin(); x!=FOLLOW_SET[i].end(); x++){
                                FOLLOW_SET[curr-128].insert(*x);
                            }             
                        }
                        if(tmp!=FOLLOW_SET[curr-128].size()) refresh=1;
                    }
                }
            }

        }
    }
    
    return;
}


void get_table(vector<vector<vector<int> > > &PRODUCTION, vector<set<int> > &FIRST_SET, vector<set<int> > &FOLLOW_SET){
    for(int i=0; i<PRODUCTION.size(); i++){
        cout<<"not det:"<<i+128<<endl;
        for(int j=0; j<PRODUCTION[i].size(); j++){
            int eps_count=0;
            if(PRODUCTION[i][j][0]==epsilon){//case:A->epsilon
                for(auto m=FOLLOW_SET[i].begin(); m!=FOLLOW_SET[i].end(); m++){
                    if((*m)!=epsilon&&(*m)<100||(*m)==FSHARP){
                        cout<<"case:"<<*m<<endl<<i+128<<"->";
                        for(int n=0; n<PRODUCTION[i][j].size(); n++){
                            cout<<PRODUCTION[i][j][n]<<' ';
                        }
                        cout<<endl;
                    }
                }
                break;
            }
            for(int k=0; k<PRODUCTION[i][j].size(); k++){       
                if(PRODUCTION[i][j][k]<100){
                    cout<<"case:"<<PRODUCTION[i][j][k]<<endl<<i+128<<"->";
                    for(int n=0; n<PRODUCTION[i][j].size(); n++){
                        cout<<PRODUCTION[i][j][n]<<' ';
                    }
                    cout<<endl;
                    break;
                }
                else{
                    int s=PRODUCTION[i][j][k]-128;
                    for(auto m=FIRST_SET[s].begin(); m!=FIRST_SET[s].end(); m++){
                        if((*m)<100&&(*m)!=epsilon){
                            cout<<"case:"<<*m<<endl<<i+128<<"->";
                            for(int n=0; n<PRODUCTION[i][j].size(); n++){
                                cout<<PRODUCTION[i][j][n]<<' ';
                            }
                            cout<<endl;
                        }
                    }

                    if(FIRST_SET[s].find(epsilon)!=FIRST_SET[s].end()) eps_count++;
                    else break;
                }
            }
            if(eps_count==PRODUCTION[i][j].size()){//generate eps indirectly
                for(auto m=FOLLOW_SET[i].begin(); m!=FOLLOW_SET[i].end(); m++){
                    if(*m!=epsilon&&*m<100||*m==FSHARP){
                        cout<<"case:"<<*m<<endl<<i+128<<"->";
                        for(int n=0; n<PRODUCTION[i][j].size(); n++){
                            cout<<PRODUCTION[i][j][n]<<' ';
                        }
                        cout<<endl;
                    }
                }
            }
        }
        
    }

}



int main(int argc, char** argv){

    vector<vector<vector<int> > > PRODUCTION;
    vector<vector<int> > SINGLE_PRODUCTION;
    vector<int> EACH_SINGLE_PRODUCTION;

    vector<set<int> > FIRST_SET;
    vector<set<int> > FOLLOW_SET;
    vector<set<int> > SELECT_SET;

    /*for program */
    EACH_SINGLE_PRODUCTION.push_back(programhead);
    EACH_SINGLE_PRODUCTION.push_back(block);
    EACH_SINGLE_PRODUCTION.push_back(DOT);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for programhead */
    EACH_SINGLE_PRODUCTION.push_back(K_PROGRAM);
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(SEMICOLON);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for block */
    EACH_SINGLE_PRODUCTION.push_back(constexp);
    EACH_SINGLE_PRODUCTION.push_back(varexp);
    EACH_SINGLE_PRODUCTION.push_back(prodef);
    EACH_SINGLE_PRODUCTION.push_back(compsent);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for constexp --with epsilon*/
    EACH_SINGLE_PRODUCTION.push_back(K_CONST);
    EACH_SINGLE_PRODUCTION.push_back(constdef);
    EACH_SINGLE_PRODUCTION.push_back(constsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for constdef */
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(O_EQUAL);
    EACH_SINGLE_PRODUCTION.push_back(INT);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for varexp */
    EACH_SINGLE_PRODUCTION.push_back(K_VAR);
    EACH_SINGLE_PRODUCTION.push_back(vardef);
    EACH_SINGLE_PRODUCTION.push_back(varsuff);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for constsuff */
    EACH_SINGLE_PRODUCTION.push_back(O_COMMA);
    EACH_SINGLE_PRODUCTION.push_back(constdef);
    EACH_SINGLE_PRODUCTION.push_back(constsuff);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for vardef */
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(idsuff);
    EACH_SINGLE_PRODUCTION.push_back(COLON);
    EACH_SINGLE_PRODUCTION.push_back(type);
    EACH_SINGLE_PRODUCTION.push_back(SEMICOLON);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for varsuff */
    EACH_SINGLE_PRODUCTION.push_back(vardef);
    EACH_SINGLE_PRODUCTION.push_back(varsuff);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for prodef */
    EACH_SINGLE_PRODUCTION.push_back(prohead);
    EACH_SINGLE_PRODUCTION.push_back(block);
    EACH_SINGLE_PRODUCTION.push_back(SEMICOLON);
    EACH_SINGLE_PRODUCTION.push_back(prosuff);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for type */
    EACH_SINGLE_PRODUCTION.push_back(K_LONG);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(K_INTEGER);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for prohead */
    EACH_SINGLE_PRODUCTION.push_back(K_PROCEDURE);
    EACH_SINGLE_PRODUCTION.push_back(argument);
    EACH_SINGLE_PRODUCTION.push_back(SEMICOLON);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    

    /*for prosuff */
    EACH_SINGLE_PRODUCTION.push_back(prohead);
    EACH_SINGLE_PRODUCTION.push_back(block);
    EACH_SINGLE_PRODUCTION.push_back(SEMICOLON);
    EACH_SINGLE_PRODUCTION.push_back(prosuff);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for assign_or_call */
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(suffix);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for sentence */
    EACH_SINGLE_PRODUCTION.push_back(assign_or_call);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(ifsent);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(whilesent);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(read);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(write);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(compsent);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for suffix */
    EACH_SINGLE_PRODUCTION.push_back(ASSIGN);
    EACH_SINGLE_PRODUCTION.push_back(express);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(L_PAREN);
    EACH_SINGLE_PRODUCTION.push_back(express);
    EACH_SINGLE_PRODUCTION.push_back(R_PAREN);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for ifsent */
    EACH_SINGLE_PRODUCTION.push_back(K_IF);
    EACH_SINGLE_PRODUCTION.push_back(condition);
    EACH_SINGLE_PRODUCTION.push_back(K_THEN);
    EACH_SINGLE_PRODUCTION.push_back(sentence);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for read */
    EACH_SINGLE_PRODUCTION.push_back(K_READ);
    EACH_SINGLE_PRODUCTION.push_back(L_PAREN);
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(idsuff);
    EACH_SINGLE_PRODUCTION.push_back(R_PAREN);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for whilesent */
    EACH_SINGLE_PRODUCTION.push_back(K_WHILE);
    EACH_SINGLE_PRODUCTION.push_back(condition);
    EACH_SINGLE_PRODUCTION.push_back(K_DO);
    EACH_SINGLE_PRODUCTION.push_back(sentence);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for idsuff */
    EACH_SINGLE_PRODUCTION.push_back(O_COMMA);
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(idsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for write */
    EACH_SINGLE_PRODUCTION.push_back(K_WRITE);
    EACH_SINGLE_PRODUCTION.push_back(L_PAREN);
    EACH_SINGLE_PRODUCTION.push_back(express);
    EACH_SINGLE_PRODUCTION.push_back(exprsuff);
    EACH_SINGLE_PRODUCTION.push_back(R_PAREN);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for compsent */
    EACH_SINGLE_PRODUCTION.push_back(K_BEGIN);
    EACH_SINGLE_PRODUCTION.push_back(sentence);
    EACH_SINGLE_PRODUCTION.push_back(sentsuff);
    EACH_SINGLE_PRODUCTION.push_back(K_END);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for exprsuff */
    EACH_SINGLE_PRODUCTION.push_back(O_COMMA);
    EACH_SINGLE_PRODUCTION.push_back(express);
    EACH_SINGLE_PRODUCTION.push_back(exprsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for sentsuff */
    EACH_SINGLE_PRODUCTION.push_back(SEMICOLON);
    EACH_SINGLE_PRODUCTION.push_back(sentence);
    EACH_SINGLE_PRODUCTION.push_back(sentsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for condition */
    EACH_SINGLE_PRODUCTION.push_back(express);
    EACH_SINGLE_PRODUCTION.push_back(relationopt);
    EACH_SINGLE_PRODUCTION.push_back(express);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(K_ODD);
    EACH_SINGLE_PRODUCTION.push_back(express);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for termsuff */
    EACH_SINGLE_PRODUCTION.push_back(addopt);
    EACH_SINGLE_PRODUCTION.push_back(term);
    EACH_SINGLE_PRODUCTION.push_back(termsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for express */
    EACH_SINGLE_PRODUCTION.push_back(O_ADD);
    EACH_SINGLE_PRODUCTION.push_back(term);
    EACH_SINGLE_PRODUCTION.push_back(termsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_MUS);
    EACH_SINGLE_PRODUCTION.push_back(term);
    EACH_SINGLE_PRODUCTION.push_back(termsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(term);
    EACH_SINGLE_PRODUCTION.push_back(termsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for term */
    EACH_SINGLE_PRODUCTION.push_back(factor);
    EACH_SINGLE_PRODUCTION.push_back(factorsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for factorsuff */
    EACH_SINGLE_PRODUCTION.push_back(mulopt);
    EACH_SINGLE_PRODUCTION.push_back(factor);
    EACH_SINGLE_PRODUCTION.push_back(factorsuff);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);

    SINGLE_PRODUCTION.clear();

    /*for argument */
    EACH_SINGLE_PRODUCTION.push_back(L_PAREN);
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    EACH_SINGLE_PRODUCTION.push_back(COLON);
    EACH_SINGLE_PRODUCTION.push_back(type);
    EACH_SINGLE_PRODUCTION.push_back(R_PAREN);

    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(epsilon);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    PRODUCTION.push_back(SINGLE_PRODUCTION);

    EACH_SINGLE_PRODUCTION.clear();
    SINGLE_PRODUCTION.clear();

    /*for factor */
    EACH_SINGLE_PRODUCTION.push_back(IDENTIFIER);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(INT);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(L_PAREN);
    EACH_SINGLE_PRODUCTION.push_back(express);
    EACH_SINGLE_PRODUCTION.push_back(R_PAREN);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for addopt */
    EACH_SINGLE_PRODUCTION.push_back(O_ADD);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_MUS);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for mulopt */
    EACH_SINGLE_PRODUCTION.push_back(O_MUL);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_DIV);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    /*for relationopt */
    EACH_SINGLE_PRODUCTION.push_back(O_EQUAL);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_NOT_EQUAL);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_LESS);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_LESS_EQUAL);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_GREATER);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    EACH_SINGLE_PRODUCTION.push_back(O_GREATER_EQUAL);
    SINGLE_PRODUCTION.push_back(EACH_SINGLE_PRODUCTION);
    EACH_SINGLE_PRODUCTION.clear();

    PRODUCTION.push_back(SINGLE_PRODUCTION);
    SINGLE_PRODUCTION.clear();

    cout<<"production:"<<endl;
    for(int i=0; i<PRODUCTION.size(); i++){
        for(int j=0; j<PRODUCTION[i].size(); j++){
            cout<<i+128<<':';
            for(int k=0; k<PRODUCTION[i][j].size(); k++){
                cout<<PRODUCTION[i][j][k]<<' ';
            }
            cout<<endl;
        } 
    }
    cout<<endl;
/*----------------------------------------------*/
    FIRST_SET.resize(PRODUCTION.size());
    cout<<"FIRST SET:"<<endl;
    for(int i=0; i<PRODUCTION.size(); i++){
        get_first(i, PRODUCTION, FIRST_SET);
    }

    for(int i=0; i<FIRST_SET.size(); i++){//print FIRST set
        cout<<i+128<<':';
        for(auto j=FIRST_SET[i].begin(); j!=FIRST_SET[i].end(); j++){
            cout<<*j<<' ';
        }
        cout<<endl;
    }
/*----------------------------------------------*/
    FOLLOW_SET.resize(PRODUCTION.size());
    for(int i=0; i<PRODUCTION.size(); i++){
        FOLLOW_SET[i].insert(FSHARP);
    }

    cout<<"FOLLOW SET:"<<endl;
    for(int i=0; i<PRODUCTION.size(); i++){
        FOLLOW_SET[i].insert(FSHARP);
    }

    get_follow(PRODUCTION, FIRST_SET, FOLLOW_SET);

    for(int i=0; i<FOLLOW_SET.size(); i++){//print FOLLOW set
        cout<<i+128<<':';
        for(auto j=FOLLOW_SET[i].begin(); j!=FOLLOW_SET[i].end(); j++){
            cout<<*j<<' ';
        }
        cout<<endl;
    }
/*----------------------------------------------*/
    get_table(PRODUCTION, FIRST_SET, FOLLOW_SET);
    
/*----------------------------------------------*/
    




    return 0;
}
