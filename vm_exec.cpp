#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

using namespace std;


enum{
    TINT,
    TCH,
    TSTR,
    TD,
    TADDR,
    TSTRUCT
};

class Var{
private:
    struct VarNode{
        union{
            char *sval;
            char ch;
            long long int ival;
            long double dval;

            void *pval;
        };

        int kind_type;
        string label;
        bool is_localvar=false;
    };

    struct StructVal{
        vector<struct VarNode> dictVarsStruct;
        string labelstruct;
        int id_var;
        bool is_localvar=false;
    };


public:
    VarNode var;
    struct StructVal varstruct;
    int id_var;
    bool operator ==(Var eq){
        if(this->var.kind_type != eq.var.kind_type) return false;
        switch(this->var.kind_type){
            case TINT:{

                if(this->var.ival != eq.var.ival) return false;
            }
            case TADDR:{
                if(this->var.pval != eq.var.pval) return false;
            }
            case TCH:{
                if(this->var.ch != eq.var.ch) return false;
            }
            case TD:{
                if(this->var.dval != eq.var.dval) return false;
            }
            case TSTR:{
                if(strcmp(this->var.sval,eq.var.sval) != 0) return false;
            }
            case TSTRUCT:{
                break;
            }

        }
        return true;
    }
};

class Struct : private Var{
public:


    StructVal var;

    bool operator ==(Var eq){
        if(this->var.kind_type != eq.var.kind_type) return false;
        switch(this->var.kind_type){
            case TINT:{

                if(this->var.ival != eq.var.ival) return false;
            }
            case TADDR:{
                if(this->var.pval != eq.var.pval) return false;
            }
            case TCH:{
                if(this->var.ch != eq.var.ch) return false;
            }
            case TD:{
                if(this->var.dval != eq.var.dval) return false;
            }
            case TSTR:{
                if(strcmp(this->var.sval,eq.var.sval) != 0) return false;
            }
        }
        return true;
    }
};


vector<Var> mapVars;
vector<Var> CurFuncVars;

std::map<string,Var> SysRegs;

void init_sys(void){

}


void RegVar(Var *tmp,bool is_local=false){
    if(!is_local) mapVars.insert(mapVars.end(),*tmp);
    else{
        CurFuncVars.insert(CurFuncVars.end(),*tmp);
        CurFuncVars[CurFuncVars.end()].var.is_localvar=true;

        mapVars.insert(mapVars.end(),*tmp);

        mapVars[mapVars.end()].var.is_localvar=true;
        return mapVars
    }

}

void DelVar(Var *find_var,bool is_local=true){

    for (vector<Var>::iterator it = mapVars.begin(); it != mapVars.end(); it++) {
        if(*it == find_var) mapVars[it].erase(it);
    }
    if(is_local){
        for (vector<Var>::iterator it = CurFuncVars; it != CurFuncVars.end(); it++) {
            if(*it == find_var) CurFuncVars[it].erase(it);
        }
    }
    return;
}

class OperatorFuncs{
public:

    void Sum(Var arg1,Var arg2,Var &argres){
        if(arg1.var.kind_type == TDOUBLE)
        {
            if(arg1.var.kind_type == TINT) argres.var.dval=(long double)arg1.var.ival+arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg1.var.kind_type == TINT)
        {
            if(arg1.var.kind_type == TINT) argres.var.ival=arg1.var.ival+(long long int)arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TDOUBLE)
        {
            if(arg12var.kind_type == TINT) argres.var.dval=(long double)arg2.var.ival+arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TINT)
        {
            if(arg2.var.kind_type == TINT) argres.var.ival=arg2.var.ival+(long long int)arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }

    }
    void Sub(Var arg1,Var arg2,Var &argres){
        if(arg1.var.kind_type == TDOUBLE)
        {
            if(arg1.var.kind_type == TINT) argres.var.dval=(long double)arg1.var.ival-arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg1.var.kind_type == TINT)
        {
            if(arg1.var.kind_type == TINT) argres.var.ival=arg1.var.ival-(long long int)arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TDOUBLE)
        {
            if(arg12var.kind_type == TINT) argres.var.dval=(long double)arg2.var.ival-arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TINT)
        {
            if(arg2.var.kind_type == TINT) argres.var.ival=arg2.var.ival-(long long int)arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
    }
    void Pow(Var arg1,Var arg2,Var argres){
        if(arg1.var.kind_type == TDOUBLE)
        {
            if(arg1.var.kind_type == TINT) argres.var.dval=(long double)arg1.var.iva*arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg1.var.kind_type == TINT)
        {
            if(arg1.var.kind_type == TINT) argres.var.ival=arg1.var.ival*(long long int)arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TDOUBLE)
        {
            if(arg12var.kind_type == TINT) argres.var.dval=(long double)arg2.var.ival*arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TINT)
        {
            if(arg2.var.kind_type == TINT) argres.var.ival=arg2.var.ival*(long long int)arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
    }
    void Div(Var arg1,Var arg2,Var argres){
        if(arg1.var.kind_type == TDOUBLE)
        {
            if(arg1.var.kind_type == TINT) argres.var.dval=(long double)arg1.var.ival/arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg1.var.kind_type == TINT)
        {
            if(arg1.var.kind_type == TINT) argres.var.ival=arg1.var.ival/(long long int)arg1.var.dval;
            if(arg1.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TDOUBLE)
        {
            if(arg12var.kind_type == TINT) argres.var.dval=(long double)arg2.var.ival/arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
        if(arg2.var.kind_type == TINT)
        {
            if(arg2.var.kind_type == TINT) argres.var.ival=arg2.var.ival/(long long int)arg2.var.dval;
            if(arg2.var.kind_type == TDOUBLE) return;
        }
    }
};

bool add_loc_var=false;

int AnalyseCommand(string command , string arg1 , string arg2){
    bool is_loc = add_loc_var;
    if(command == "addvar"){ // add variable-command
        Var newvar;
        if(arg1 == "int"){
            newvar.var.kind_type=TINT;
            newvar.var.ival=0;
            RegVar(newvar,is_loc);
        }
        if(arg1 == "double"){
            newvar.var.kind_type=TD;
            newvar.var.ival=0;
            RegVar(newvar,is_loc);
        }
        if(arg1 == "char"){
            newvar.var.kind_type=TCH;
            newvar.var.ival=0;
            RegVar(newvar,is_loc);
        }
        if(arg1 == "string"){
            newvar.var.kind_type=TSTR;
            newvar.var.ival=0;
            RegVar(newvar,is_loc);
        }
        if(arg1 == "ptr"){
            newvar.var.kind_type=TADDR;
            newvar.var.ival=0;
            RegVar(newvar,is_loc);
        }
    }
    if(command == "add"){ // math + operator

    }
    if(command == "sub"){ // math - operator

    }
    if(command == "pow"){ // math * operator

    }
    if(command == "div"){ // math / operator

    }
    if(command == "eq"){ // bin = operator

    }
    if(command == "xor"){ // bin ^ operator

    }
    if(command == "if"){ // logic if operator

    }
}



void Exec(string filename){
    std::ifstream codefile(filename, std::ios::in);
    int DEF_FUNC=100,DEF_VAR=200,ENDDEF_FUNC=1;
    string arg1,arg2;
    if(codefile.fail())
    {
        std::cerr << "Cannot to open file\n";
    }

    while(!codefile.eof()){
        codefile >> command;
        codefile.getline(arg1,256,',');
        codefile.getline(arg2,256,',');
        if(command == "newvar" && is_func) AnalyseCommand(command,arg1,arg2);
        else{
            int res=AnalyseCommand(command,arg1,arg2);
            if(res == DEF_FUNC) add_loc_var=true;
            if(res == ENDDEF_FUNC) add_loc_var=false;
        }


    }
}


int main()
{
    cout << "hello world";
}
