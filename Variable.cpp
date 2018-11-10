#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>

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
public:
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

void init_sysreg(void){

	SysRegs.insert(std::pair<string,Var>("ASave",{id_var : 0;var.kind_type : TADDR;var.paddr=0x0;var.label : "ASave"}));
	SysRegs.insert(std::pair<string,Var>("Isave",{id_var : 0;var.kind_type : TINT;var.ival=0;var.label : "Isave"}));
	SysRegs.insert(std::pair<string,Var>("Ssave",{id_var : 0;var.kind_type : TSTR;var.sval=0;var.label : "Ssave"}));
	SysRegs.insert(std::pair<string,Var>("Csave",{id_var : 0;var.kind_type : TCH;var.ch=0;var.label : "Csave"}));
	SysRegs.insert(std::pair<string,Var>("Dsave",{id_var : 0;var.kind_type : TD;var.dval=0;var.label : "Dsave"}));
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


