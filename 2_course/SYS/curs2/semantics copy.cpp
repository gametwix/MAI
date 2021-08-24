/* $j22 */
#include "semantics.h"
using namespace std;
void tSM::init(){
	globals.clear();
	locals.clear();
	params.clear();
	scope =0;
	
	globals["pi"] = tgName(VAR|DEFINED|BUILT);					//const double pi
	globals["e"] = tgName(VAR|DEFINED|BUILT);					//const double e
	globals["display"] = tgName(PROC|DEFINED|BUILT,"", 1);		//inline double display(double x)
	globals["newline"] = tgName(PROC|DEFINED|BUILT,"", 0);		//inline double newline()
	globals["quotient"] = tgName(PROC|DEFINED|BUILT,"", 2);		//inline double quotient(double x, double y)
	globals["expt"] = tgName(PROC|DEFINED|BUILT,"", 2);			//inline double expt(double x, double y)
	globals["sin"] = tgName(PROC|DEFINED|BUILT,"", 1);			//std::sin
	globals["cos"] = tgName(PROC|DEFINED|BUILT,"", 1);			//std::cos
	globals["tan"] = tgName(PROC|DEFINED|BUILT,"", 1);			//std::tan
	globals["exp"] = tgName(PROC|DEFINED|BUILT,"", 1);			//std::exp
	globals["atan"] = tgName(PROC|DEFINED|BUILT,"", 1);			//std::atan
	globals["sqrt"] = tgName(PROC|DEFINED|BUILT,"", 1);			//std::sqrt
	globals["abs"] = tgName(PROC|DEFINED|BUILT,"", 1);			//inline double abs(double x)
	globals["remainder"] = tgName(PROC|DEFINED|BUILT,"", 2);	//inline double remainder(double x, double y)
	return;}
int tSM::p01(){ //       S -> PROG
	bool error = false;
	for(auto& elem:globals){
		if(!elem.second.test(DEFINED)){
			error = true;
			if(elem.second.test(PROC)){
				ferror_message+= "Error[01-2] in line "+ elem.second.line +": Procedure '" + elem.first + "' used, but not defined\n";
				//Процедура 'f' использована, но не определена
				//Procedure 'f' used, but not defined
			}
			if(elem.second.test(VAR)){
				ferror_message+= "Error[01-2] in line "+ elem.second.line +": Variable '" + elem.first + "' used, but not defined\n";
				//Переменная 'f' использована, но не определена
				//Variable 'f' used, but not defined
			}
		}
		if(!elem.second.test(USED) && !elem.second.test(BUILT)){
			if(elem.second.test(PROC)){
				ferror_message+= "Error[01-3] in line "+ elem.second.line +": Procedure '" + elem.first + "' is defined but not used\n";
				//Процедура  'f' определена, но не использована
				//Procedure 'f' is defined but not used
			}
			if(elem.second.test(VAR)){
				ferror_message+= "Error[01-4] in line "+ elem.second.line +": Variable '" + elem.first + "' is defined, but not used\n";
				//Переменная 'f' определена, но не использована
				//Variable 'f' is defined, but not used
			}
		}
	}
	if(error) return 1;
	return 0;}
int tSM::p02(){ //    PROG -> CALCS
	return 0;}
int tSM::p03(){ //    PROG -> DEFS
	return 0;}
int tSM::p04(){ //    PROG -> DEFS CALCS
	return 0;}
int tSM::p05(){ //       E -> $id
	string name = S1->name;
	switch(scope){
		case 2:
			if(locals.count(name))break;
    	case 1:
			if(params.count(name))break;
		default:
			tgName& ref = globals[name];
			if(ref.empty()){
				ref = tgName(VAR|USED, S1->line);
            	break;
			}else if(ref.test(VAR)){
             	ref.set(USED);
            	break;
      		}else if(ref.test(BUILT)){
				ferror_message+= "Error[05-1] in line "+ S1->line +": The built-in procedure '" + 
					name + "' cannot be used as a variable name\n";
				//Встроенная процедура 'abs' не может быть использована в качестве имени переменной
				//The built-in procedure 'abs' cannot be used as a variable name
				return 1;
			}else if(ref.test(PROC)){
				ferror_message+= "Error[05-2] in line "+ S1->line +": The '" + name + 
					"' procedure - declared in line " + ref.line + ", cannot be used as a variable name\n";
				//Процедура 'test' - объявленная в строке 10 , не может быть использована в качестве имени переменной
				//The 'test' procedure-declared in line 10, cannot be used as a variable name
				return 1;
			}
	}
	return 0;}
int tSM::p06(){ //       E -> $int
	return 0;}
int tSM::p07(){ //       E -> $dec
	return 0;}
int tSM::p08(){ //       E -> AREX
	return 0;}
int tSM::p09(){ //       E -> COND
	return 0;}
int tSM::p10(){ //       E -> CPROC
	return 0;}
int tSM::p11(){ //    AREX -> HAREX E )
	return 0;}
int tSM::p12(){ //   HAREX -> ( AROP
	return 0;}
int tSM::p13(){ //   HAREX -> HAREX E
	return 0;}
int tSM::p14(){ //    AROP -> +
	return 0;}
int tSM::p15(){ //    AROP -> -
	return 0;}
int tSM::p16(){ //    AROP -> *
	return 0;}
int tSM::p17(){ //    AROP -> /
	return 0;}
int tSM::p18(){ //   CPROC -> HCPROC )
	tgName& ref = globals[S1->name];
	if(ref.line == S1->line) ref.arity = S1->count;
	if(ref.arity != S1->count){
		ferror_message+= "Error[18-1] in line "+ S1->line +": Number of parameters when calling the procedure - " +
			to_string(S1->count) + ", does not match the number when declaring - " + to_string(ref.arity) + "\n";
		//Количество параметров при вызове процедуры - 3, не совпадает с количеством при объявлении - 2
		//Number of parameters when calling the procedure - 3, does not match the number when declaring-2
		return 1;
	}
	return 0;}
int tSM::p19(){ //  HCPROC -> ( $id
	string name = S2->name;
	S1->count = 0;
	S1->name = S2->name;
	S1->line = S2->line;
	switch(scope){
		case 2:
			if(locals.count(name)){
				ferror_message+= "Error[19-1] in line "+ S2->line +": Using the name of the local variable '" + S2->name + "', as the name of the proceduren";
				//Использование имени локальной переменной 'test', в качестве имени процедуры
				//Using the name of the local variable 'test', as the name of the procedure
				return 1;
			}
		case 1:
			if(params.count(name)){
				ferror_message+= "Error[19-2] in line "+ S2->line +": Using the procedure parameter name '" + S2->name + "', as the procedure name\n";
				//Использование имени параметра процедуры 'test', в качестве имени процедуры
				//Using the procedure parameter name 'test', as the procedure name
				return 1;
			}
		default:
			tgName& ref = globals[name];
			if(ref.empty()){
				ref = tgName(PROC|USED, S1->line);
            	break;
			} else if(ref.test(VAR)){
             	ferror_message+= "Error[19-3] in line "+ S2->line +": Using the name of the variable '" + S2->name + "' - declared in line " + ref.line + ", as the name of the procedure\n";
				//Использование имени переменной 'test' - объявленной в строке 6, в качестве имени процедуры
				//Using the name of the variable 'test' - declared in line 6, as the name of the procedure
            	return 1;
      		}else ref.set(USED);
	}
	return 0;}
int tSM::p20(){ //  HCPROC -> HCPROC E
	S1->count++;
	return 0;}
int tSM::p21(){ //    COND -> ( cond BRANCHES )
	return 0;}
int tSM::p22(){ //BRANCHES -> ELSE
	return 0;}
int tSM::p23(){ //BRANCHES -> CLAUS BRANCHES
	return 0;}
int tSM::p24(){ //   CLAUS -> ( BOOL CLAUSB )
	return 0;}
int tSM::p25(){ //  CLAUSB -> E
	return 0;}
int tSM::p26(){ //  CLAUSB -> INTER CLAUSB
	return 0;}
int tSM::p27(){ //    ELSE -> ( else ELSEB )
	return 0;}
int tSM::p28(){ //   ELSEB -> E
	return 0;}
int tSM::p29(){ //   ELSEB -> INTER ELSEB
	return 0;}
int tSM::p30(){ //     STR -> $str
	return 0;}
int tSM::p31(){ //     STR -> SIF
	return 0;}
int tSM::p32(){ //     SIF -> ( if BOOL STR STR )
	return 0;}
int tSM::p33(){ //    BOOL -> $bool
	return 0;}
int tSM::p34(){ //    BOOL -> $idq
	string name = S1->name;
	if(scope == 1 && !params.count(name)){
		ferror_message+= "Error[34-1] in line "+ S1->line +": The '" + name + "' variable is not a procedure parameter\n";
		//Переменная 'name' не является параметром процедуры
		//The 'name' variable is not a procedure parameter
		return 1;
	}
	/*
	string name = S1->name;
	switch(scope){
		case 2:
			if(locals.count(name))break;
    	case 1:
			if(params.count(name))break;
		default:
			tgName& ref = globals[name];
			if(ref.empty()){
				ref = tgName(VAR|USED, S1->line);
            	break;
			}else if(ref.test(VAR)){
             	ref.set(USED);
            	break;
      		}else if(ref.test(BUILT)){
				ferror_message+= "Error[34-1] in line "+ S1->line +": встроенная процедура " + name + " не может быть использованна в качестве имени переменной\n";
				return 1;
			}else if(ref.test(PROC)){
				ferror_message+= "Error[34-2] in line "+ S1->line +": процедура " + name + " не может быть использованна в качестве имени переменной\n";
				return 1;
			}
	}
	*/
	return 0;}
int tSM::p35(){ //    BOOL -> REL
	return 0;}
int tSM::p36(){ //    BOOL -> OR
	return 0;}
int tSM::p37(){ //    BOOL -> CPRED
	return 0;}
int tSM::p38(){ //   CPRED -> HCPRED )
	tgName& ref = globals[S1->name];
	if(ref.line == S1->line) ref.arity = S1->count;
	if(ref.arity != S1->count){
		ferror_message+= "Error[38-1] in line "+ S1->line +": Number of parameters when calling the procedure - " +
			to_string(S1->count) + ", does not match the number when declaring - " + to_string(ref.arity) + "\n";
		//Количество параметров при вызове процедуры - 3, не совпадает с количеством при объявлении - 2
		//Number of parameters when calling the procedure - 3, does not match the number when declaring-2
		return 1;
	}
	return 0;}
int tSM::p39(){ //  HCPRED -> ( $idq
	string name = S2->name;
	S1->count = 0;
	S1->line = S2->line;
	S1->name = S2->name;
	switch(scope){
		/*
		case 2:
			if(locals.count(name)){
				ferror_message+= "Error[39-1] in line "+ S2->line +": использование имени локальной переменной " + S2->name + ", в качестве имени процедуры\n";
				return 1;
			}
			*/
		case 1:
			if(params.count(name)){
				ferror_message+= "Error[39-1] in line "+ S2->line +": Using the procedure parameter name '" + 
					S2->name + "', as the procedure name\n";
				//Использование имени параметра процедуры 'name', в качестве имени процедуры
				//Using the procedure parameter name 'name', as the procedure name
				return 1;
			}
		default:
			tgName& ref = globals[name];
			if(ref.empty()){
				ref = tgName(PROC|USED, S1->line);
            	break;
			/*} else if(ref.test(VAR)){
             	ferror_message+= "Error[39-2] in line "+ S2->line +": использование имени переменной " + S2->name + ", в качестве имени процедуры\n";
            	return 1;*/
      		}else ref.set(USED);
	}
	return 0;}
int tSM::p40(){ //  HCPRED -> HCPRED ARG
	S1->count++;
	tgName& ref = globals[S1->name];
	int step = 1 << (S1->count - 1);
	int type = S2->name == "double" ? 1 : 0;
	if(ref.line == S1->line){
		ref.types = ref.types | (type*step);
	}else{
		if(!((ref.types & (step)) == (type*step))){
			ferror_message+= "Error[40-1] in line "+ S2->line +": Using an invalid procedure parameter - " 
				+ (type == 1 ? "id" : "idq") + ", instead of " + (type == 1 ? "idq" : "id") + "\n";
			//Использование неверного параметра процедуры - id, вместо idq
			//Using an invalid procedure parameter-id, instead of id
			return 1;
		}
	}

	return 0;}
int tSM::p41(){ //     ARG -> E
	S1->name = "double";
	return 0;}
int tSM::p42(){ //     ARG -> BOOL
	S1->name = "bool";
	return 0;}
int tSM::p43(){ //     REL -> ( = E E )
	return 0;}
int tSM::p44(){ //     REL -> ( >= E E )
	return 0;}
int tSM::p45(){ //      OR -> HOR BOOL )
	return 0;}
int tSM::p46(){ //     HOR -> ( or
	return 0;}
int tSM::p47(){ //     HOR -> HOR BOOL
	return 0;}
int tSM::p48(){ //     SET -> HSET E )
	return 0;}
int tSM::p49(){ //    HSET -> ( set! $id
	string name = S3->name;
	if(scope == 2 && locals.count(name) == 1){
		ferror_message+= "Error[49-1] in line "+ S3->line +": You cannot override the local variable '" + 
			S3->name + "'\n";
		//Нельзя переопределять локальную переменную 'name'
		//You cannot override the local variable 'name'
		return 1;
	}
	if(scope == 1) if(params.count(name)) return 0;
	tgName& ref = globals[name];
	if(ref.empty()){
		ref = tgName(VAR|USED, S1->line);
		return 0;
	}else if(ref.test(VAR)){
		ref.set(USED);
		return 0;
	}else if(ref.test(BUILT)){
		ferror_message+= "Error[49-2] in line "+ S3->line +": The built-in procedure '" + 
			name + "' cannot be used as a variable name\n";
		//Встроеная процедура 'name' не может быть использована в качестве имени переменной
		// The built-in procedure 'name' cannot be used as a variable name
		return 1;
	}else if(ref.test(PROC)){
		ferror_message+= "Error[49-3] in line "+ S3->line +": The procedure '" + name + "'- declared in line " + 
		ref.line +",cannot be used as a variable name\n";
		//Процедура 'name' - обявленая в строке 15, не может быть использована в качестве имени переменной
		//The procedure 'name' - declared in line 15, cannot be used as a variable name
		return 1;
	}
	return 0;}
int tSM::p50(){ // DISPSET -> ( display E )
	return 0;}
int tSM::p51(){ // DISPSET -> ( display BOOL )
	return 0;}
int tSM::p52(){ // DISPSET -> ( display STR )
	return 0;}
int tSM::p53(){ // DISPSET -> ( newline )
	return 0;}
int tSM::p54(){ // DISPSET -> SET
	return 0;}
int tSM::p55(){ //   INTER -> DISPSET
	return 0;}
int tSM::p56(){ //   INTER -> E
	return 0;}
int tSM::p57(){ //   CALCS -> CALC
	return 0;}
int tSM::p58(){ //   CALCS -> CALCS CALC
	return 0;}
int tSM::p59(){ //    CALC -> E
	return 0;}
int tSM::p60(){ //    CALC -> BOOL
	return 0;}
int tSM::p61(){ //    CALC -> STR
	return 0;}
int tSM::p62(){ //    CALC -> DISPSET
	return 0;}
int tSM::p63(){ //    DEFS -> DEF
	return 0;}
int tSM::p64(){ //    DEFS -> DEFS DEF
	return 0;}
int tSM::p65(){ //     DEF -> PRED
	return 0;}
int tSM::p66(){ //     DEF -> VAR
	return 0;}
int tSM::p67(){ //     DEF -> PROC
	return 0;}
int tSM::p68(){ //    PRED -> HPRED BOOL )
	scope = 0;
	params.clear();
	return 0;}
int tSM::p69(){ //   HPRED -> PDPAR )
	scope = 1;
	tgName& ref = globals[S1->name];
	if(ref.line == S1->line) ref.arity = S1->count;
	if(ref.arity != S1->count){
		ferror_message+= "Error[69-1] in line "+ S1->line +": he number of parameters when calling the procedure is " +
			to_string(S1->count) + ", does not match the number when declaring - " + to_string(ref.arity) + " in line " +
			ref.line + "\n";
		//Количество параметров при вызове процедуры - 3, не совпадает с количеством при объявлении - 2 в строке 65
		//The number of parameters when calling the procedure is 3, does not match the number when declaring - 2 in line 65
		return 1;
	}
	return 0;}
int tSM::p70(){ //   PDPAR -> ( define ( $idq
	string name  = S4->name;
	S1->line = S4->line;
	S1->name = S4->name;
	tgName& ref = globals[name];
	if(ref.empty()){
		ref = tgName(PROC|DEFINED, S4->line);
		return 0;
	} /*else if(ref.test(VAR)){
		ferror_message+= "Error[70-1] in line "+ ref.line +": процедура " + name + " не может быть использованна в качестве имени переменной\n";
		return 1;
	} else if(ref.test(BUILT)){
		ferror_message+= "Error[70-1] in line "+ S4->line +": переопределение встроенных процедур\n";
		return 1;
	} */else if(ref.test(PROC)){
		if(ref.test(DEFINED)){
			ferror_message+= "Error[70-1] in line "+ S4->line +": Redefining the" +
			S4->name + ", procedure, first defined in line " + ref.line + "\n";
			//Повторное определение процедуры 'name', впервые была определена в строке 14
			//Redefining the 'name' procedure, first defined in line 14
			return 1;
		}else{
			ref.set(DEFINED);
		}
	}
	S1->count = 0;
	return 0;}
int tSM::p71(){ //   PDPAR -> PDPAR $idq
	S1->count++;
	tgName& ref = globals[S1->name];
	int step = 1 << (S1->count - 1);
	int type = 0;
	bool check = (ref.line != S1->line);
	if(check){
		if(!((ref.types & (step)) == (type*step))){
			ferror_message+= "Error[71-1] in line "+ ref.line +": Using an invalid procedure parameter - idq, instead of id\n";
			//Использование неверного параметра процедуры - idq, вместо id
			//Using an invalid procedure parameter - idq, instead of id
			return 1;
		}
	}else ref.types = ref.types | (type*step);
	if(params.count(S2->name)){
      	ferror_message+= "Error[71-2] in line "+ S2->line +": The '" + S1->name + "' procedure duplicates the '" + S2->name +"' parameter\n";
		//В процедуре 'func' дублируется параметр 'a'
		//The 'func' procedure duplicates the 'a' parameter
		return -1;
	}
	if(S2->name==S1->name){
    	ferror_message+= "Warning[71-3] in line " + S2->line + ": In the '" + S1->name 
			+ "' procedure, a parameter with the same name as the procedure itself\n";
		//В процедуре 'func' параметр с таким же именем, что и сама процедура
		//In the 'func' procedure, a parameter with the same name as the procedure itself
	}
	params.insert(S2->name);
	return 0;}
int tSM::p72(){ //   PDPAR -> PDPAR $id
	S1->count++;
	tgName& ref = globals[S1->name];
	int step = 1 << (S1->count - 1);
	int type = 1;
	bool check = (ref.line != S1->line);
	if(check){
		if(!((ref.types & (type*step)) == (type*step))){
			ferror_message+= "Error[72-1] in line "+ ref.line +": Using an invalid procedure parameter - id, instead of id\n";
			//Использование неверного параметра процедуры - id, вместо idq
			//Using an invalid procedure parameter - id, instead of id
			return 1;
		}
	}else ref.types = ref.types | (type*step);
	if(params.count(S2->name)){
      	ferror_message+= "Error[72-2] in line "+ S2->line +": The '" + S1->name + "' procedure duplicates the '" + S2->name +"' parameter\n";
		//В процедуре 'func' дублируется параметр 'a'
		//The 'func' procedure duplicates the 'a' parameter
		return -1;
	}
	/*if(S2->name==S1->name){
    	ferror_message+= "Warning[72-3] in line " + S2->line + ": в процедуре " + S1->name + "параметр с таким же именем\n";
	}*/
	params.insert(S2->name);
	return 0;}
int tSM::p73(){ //     VAR -> VARDCL E )
	return 0;}
int tSM::p74(){ //  VARDCL -> ( define $id
	string name = S3->name;
	tgName& ref = globals[S3->name];
	if(ref.empty()){
		ref = tgName(VAR|DEFINED, S3->line);
		return 0;
	} else if(ref.test(BUILT)){
		ferror_message+= "Error[74-1] in line "+ S3->line +": The built-in procedure '" + name 
			+ "' cannot be used as a variable name\n";
		//Встроеная процедура 'abs' не может быть использована в качестве имени переменной
		//The built-in procedure 'abs' cannot be used as a variable name
		return 1;
	} else if(ref.test(PROC)){
		ferror_message+= "Error[74-2] in line "+ S3->line +": The procedure '" + name + "'- declared in line " +
			ref.line + ", cannot be used as a variable name\n";
		//Процедура 'name' - объявленная в строке 10, не может быть использованна в качестве имени переменной
		//The procedure 'name' - declared in line 10, cannot be used as a variable name
		return 1;
	} else if(ref.test(VAR)){
		if(ref.test(DEFINED)){
			ferror_message+= "Error[74-3] in line "+ S3->line +": Redefining the '" +
				name + "' - variable-originally defined in line " + ref.line + "\n";
			//Повторное определение переменной 'name' - изначально определенной в строке 14
			//Redefining the 'name' variable-originally defined in line 14
			return 1;
		}else{
			ref.set(DEFINED);
		}
	}
	return 0;}
int tSM::p75(){ //    PROC -> HPROC BLOCK )
	scope = 0;
	params.clear();
	return 0;}
int tSM::p76(){ //    PROC -> HPROC E )
	scope = 0;
	params.clear();
	return 0;}
int tSM::p77(){ //   HPROC -> PCPAR )
	scope = 1;
	tgName& ref = globals[S1->name];
	if(ref.line == S1->line) ref.arity = S1->count;
	if(ref.arity != S1->count){
		ferror_message+= "Error[77-1] in line "+ S1->line +": The number of parameters when calling the procedure is " +
			to_string(S1->count) + ", does not match the number when declaring - " + to_string(ref.arity) + " in line" +
			ref.line + "\n";
		//Количество параметров при вызове процедуры - 3, не совпадает с количеством при объявлении - 2 в строке 65
		//The number of parameters when calling the procedure is 3, does not match the number when declaring - 2 in line 65
		return 1;
	}
	return 0;}
int tSM::p78(){ //   HPROC -> HPROC INTER
	return 0;}
int tSM::p79(){ //   PCPAR -> ( define ( $id
	string name  = S4->name;
	S1->line = S4->line;
	S1->name = S4->name;
	tgName& ref = globals[name];
	if(ref.empty()){
		ref = tgName(PROC|DEFINED, S4->line);
		return 0;
	} else if(ref.test(VAR)){
		ferror_message+= "Error[79-1] in line "+ ref.line +": Variable '" + name + "' - declared in line " + 
			ref.line +",cannot be used as a procedure name\n";
		//Переменная 'name' - объявленная в строке 17, не может быть использована в качестве имени процедуры
		//Variable 'name' - declared in line 17, cannot be used as a procedure name
		return 1;
	} else if(ref.test(BUILT)){
		ferror_message+= "Error[79-2] in line "+ S4->line +": Cannot override the built-in '" + name + "' procedure\n";
		//Невозможно переопределить встроенную процедуру 'name'
		//Cannot override the built-in 'name'procedure
		return 1;
	} else if(ref.test(PROC)){
		if(ref.test(DEFINED)){
			ferror_message+= "Error[79-3] in line "+ S4->line +": Redefining the '" +
				name + "' procedure - originally defined in line " + ref.line + "\n";
			//Повторное определение процедуры 'name' - изначально определенной в строке 14
			//Redefining the 'name' procedure-originally defined in line 14'
			return 1;
		}else{
			ref.set(DEFINED);
		}
	}
	S1->count = 0;
	return 0;}
int tSM::p80(){ //   PCPAR -> PCPAR $id
	S1->count++;
	if(params.count(S2->name)){
		ferror_message+= "Error[80-1] in line "+ S2->line +": The '" + S1->name + "' procedure duplicates the '" + S2->name +"' parameter\n";
		//В процедуре 'func' дублируется параметр 'a'
		//The 'func' procedure duplicates the 'a'parameter
		return -1;
	}
	if(S2->name==S1->name){
		ferror_message+= "Warning[80-2] in line " + S2->line + ": In the '" + S1->name 
			+ "' procedure, a parameter with the same name as the procedure itself\n";
		//В процедуре 'func' параметр с таким же именем, что и сама процедура
		//In the 'func' procedure, a parameter with the same name as the procedure itself
	}
	params.insert(S2->name);
	return 0;}
int tSM::p81(){ //   BLOCK -> HBLOCK E )
	scope = S1->count;
	return 0;}

int tSM::p82(){ //  HBLOCK -> BLVAR )
	return 0;}
int tSM::p83(){ //  HBLOCK -> HBLOCK INTER
	return 0;}
int tSM::p84(){ //   BLVAR -> ( let ( LOCDEF
	S1->count = scope;
	scope = 2;
	return 0;}
int tSM::p85(){ //   BLVAR -> BLVAR LOCDEF
	return 0;}
int tSM::p86(){ //  LOCDEF -> ( $id E )
	if(locals.count(S2->name)){
		ferror_message+= "Error[86-1] in line "+ S2->line +": Redefining the local variable '" +
		S2->name + "'\n";
		//Повторное определение переменной локальной переменной 'name'
		//Redefining the local variable 'name'
			return 1;
	}else{
		locals.insert(S2->name);
	}
	return 0;}
//_____________________
int tSM::p87(){return 0;} int tSM::p88(){return 0;} 
int tSM::p89(){return 0;} int tSM::p90(){return 0;} 
int tSM::p91(){return 0;} int tSM::p92(){return 0;} 
int tSM::p93(){return 0;} int tSM::p94(){return 0;} 
int tSM::p95(){return 0;} int tSM::p96(){return 0;} 
int tSM::p97(){return 0;} int tSM::p98(){return 0;} 
int tSM::p99(){return 0;} int tSM::p100(){return 0;} 
int tSM::p101(){return 0;} int tSM::p102(){return 0;} 
int tSM::p103(){return 0;} int tSM::p104(){return 0;} 
int tSM::p105(){return 0;} int tSM::p106(){return 0;} 
int tSM::p107(){return 0;} int tSM::p108(){return 0;} 
int tSM::p109(){return 0;} int tSM::p110(){return 0;} 


