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
    TADDR
};

class Var{
private:
    struct VarNode{
        union Val{
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



public:
    VarNode var;
    int id_var;
    bool operator ==(Var eq){
        if(this->var.kind_type != eq.var.kind_type) return false;
        switch(this->var.kind_type){
            case INT:{

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

class Struct : private Var{
public:
    struct StructVal{
        vector<struct VarNode> dictVarsStruct;
        string labelstruct;
        int id_var;
        bool is_localvar=false;
    };

    StructVal var;

    bool operator ==(Var eq){
        if(this->var.kind_type != eq.var.kind_type) return false;
        switch(this->var.kind_type){
            case INT:{

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

int main()
{
    cout << "hello world";
}
