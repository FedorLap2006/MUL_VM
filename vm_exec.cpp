#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "Variable.cpp"
#include "Operations.cpp"

using namespace std;







bool add_loc_var=false;

string CopyFromPos(string str,int pos){
	string ret;
	if(pos > str.size() || pos < 0) return "$$#error#$$";
	for (size_t it2 = pos; it2 < str.size() ; it2++) {
		ret.insert(ret.end(),str[it]);
	}
	return ret;
}

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
			newvar.var.dval=0;
			RegVar(newvar,is_loc);
		}
		if(arg1 == "char"){
			newvar.var.kind_type=TCH;
			newvar.var.ch=0;
			RegVar(newvar,is_loc);
		}
		if(arg1 == "string"){
			newvar.var.kind_type=TSTR;
			newvar.var.sval=0;
			RegVar(newvar,is_loc);
		}
		if(arg1 == "ptr"){
			newvar.var.kind_type=TADDR;
			newvar.var.pval=0x0;
			RegVar(newvar,is_loc);
		}
	}
	if(command == "add"){ // math + operator
		if(arg1[0] == '$')
		{
			string num1=CopyFromPos(arg1,1);
			switch(arg1[1])
			{
				case '%':{ // float/double
			   		string num2=CopyFromPos(arg1,2);
					map<string,Var>::iterator itreg=SysRegs.find("Dsave");
					iteg.value_type.var->dval=atof(num2.c_str());
					break;
				}
				case '@':{ // int
					string num2=CopyFromPos(arg1,2);
					map<string,Var>::iterator itreg=SysRegs.find("Isave");
					itreg.value_type.var->ival=atol(num2.c_str());
					break;
				}
				case '$':{ // sym
					string c2=CopyFromPos(arg1,2);
					map<string,Var>::iterator itreg=SysRegs.find("Csave");
					itreg.value_type.var->ch=c2[0];
					break;
				}
				case '#':{ // string
					string s2=CopyFromPos(arg1,2);
					map<string,Var>::iterator itreg=SysRegs.find("Ssave");
					itreg.value_type.var->pval=s2;	
					break;
				}
				case '&':{
					string c2=CopyFromPos(arg1,2);
					map<string,Var>::iterator itreg=SysRegs.find("Asave");
					itreg.value_type.var->pval=atol(c2.c_str());
					break;
				}
			}
		}
		if(arg2[0] == '$')
		{
			string num1=CopyFromPos(arg2,1);
			switch(arg2[1])
			{
				case '%':{ // float/double
			   		string num2=CopyFromPos(arg2,2);
					map<string,Var>::iterator itreg=SysRegs.find("Dsave");
					itreg.value_type.var->dval+=atof(num2.c_str());;
					break;
				}
				case '@':{ // int
					string num2=CopyFromPos(arg2,2);
					map<string,Var>::iterator itreg=SysRegs.find("Isave");
					itreg.value_type.var->ival+=atol(num2.c_str());
					break;
				}
				case '$':{ // sym
					string c2=CopyFromPos(arg2,2);
					map<string,Var>::iterator itreg=SysRegs.find("Csave");
					itreg.value_type.var->ch+=c2[0];
					break;
				}
				case '#':{ // string
					string s2=CopyFromPos(arg2,2);
					map<string,Var>::iterator itreg=SysRegs.find("Ssave");
					itreg.value_type.var->pval+=s2;	
					break;
				}
				case '&':{
					string c2=CopyFromPos(arg2,2);
					map<string,Var>::iterator itreg=SysRegs.find("Asave");
					itreg.value_type.var->pval+=atol(c2.c_str());
					break;
				}
			}
		}

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
