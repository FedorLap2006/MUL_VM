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


void AnalyseCommand(string command , Var arg1 , Var arg2){
    if(command == "addvar"){
        Var newvar;
        if(arg1 == "int"){
            newvar.var.kind_type=TINT;
            newvar.var.ival=0;
        }
        if(arg1 == "double"){
            newvar.var.kind_type=TD;
            newvar.var.ival=0;
        }
        if(arg1 == "char"){
            newvar.var.kind_type=TCH;
            newvar.var.ival=0;
        }
        if(arg1 == "string"){
            newvar.var.kind_type=TSTR;
            newvar.var.ival=0;
        }
        if(arg1 == "ptr"){
            newvar.var.kind_type=TADDR;
            newvar.var.ival=0;
        }
    }
    if(command == "add"){

    }
    if(command == "sub"){

    }
    if(command == "pow"){

    }
    if(command == "div"){

    }
    if(command == "eq"){

    }
    if(command == "xor"){

    }
    if(command == "if"){
        
    }
}



void Exec(string filename){
    std::ifstream codefile(filename, std::ios::in);

    if(codefile.fail())
    {
        std::cerr << "Cannot to open file\n";
    }

    while(!codefile.eof()){
        codefile >> command;
        codefile.getline(arg1,256,',');
        codefile.getline(arg2.var.label,256,',');
        AnalyseCommand(command,arg1,arg2);
    }
}


int main()
{
    cout << "hello world";
}
