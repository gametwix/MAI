:-dynamic id/2.
:-dynamic parents/3.

%основной предикат
main :-
    open('Kapetings.ged', read, Inputfile), 
	work_file(Inputfile),
	listing(parents).
	
%предикат обработки файла
work_file(Inputfile):-at_end_of_stream(Inputfile).
work_file(Inputfile):-
	\+ at_end_of_stream(Inputfile),
    read_line_to_codes(Inputfile,Codes),
    atom_chars(X, Codes),
	split_string(X," ","", List),
	work_line(Inputfile,List), 
	work_file(Inputfile), !.
  
%обработка строки вида "0 @...@ INDI ..."
work_line(Inputfile,[H,Y,Z|_]):-H="0", 
								Z="INDI",
								read_string(Inputfile, "\n", "\r", End, String),
								split_string(String," ","", List),
								character_count(Inputfile, Pos),
								name(Inputfile,List,Pos,N),
								assertz(id(Y,N)),!. %занесение в базу данных

%обработка строки вида "0 @...@ FAM ..."								
work_line(Inputfile,[H,Y,Z|_]):-H="0", 
								Z="FAM",
								read_string(Inputfile, "\n", "\r", End, String),
								split_string(String," ","", List),
								rodstvo(Inputfile,List),!.

%если строка не подходит под первые два описания								
work_line(Inputfile,[H,Y,Z]):-(H \= "0";
							  (Z \= "INDI",
							   Z \= "FAM")),!.						
work_line(_,[H,Z]):-!.
work_line(_,[A,B,C,D]):-!.
work_line(_,[A,B,C,D,E]):-!.
work_line(_,[A,B,C,D,E,F]):-!.
work_line(_,[A,B,C,D,E,F,G]):-!.

%обработка строки вида "1 HUSB ..."
rodstvo(Inputfile,[X,Y,T]):-X="1",
							Y="HUSB",
							read_string(Inputfile, "\n", "\r", End, String),
							split_string(String," ","", [A,B,C]),
							read_string(Inputfile, "\n", "\r", End, String1),
							split_string(String1," ","", List2),
							child(T,C,Inputfile,List2),!.
%если строка не подходит					
rodstvo(Inputfile,[X,Y,T]):- (X \= "1";
							  Y \= "HUSB"),
							  read_string(Inputfile, "\n", "\r", End, String),
							  split_string(String," ","", List),
							  rodstvo(Inputfile,List).

%обработка строк вида "1 CHIL ..."
child(Fid,Mid,Inputfile,[X,Y,Z]):-X="1", 
								  Y="CHIL",
								  id(Fid,F),
								  id(Mid,M),
								  id(Z,C),
								  assert(parents(C,F,M)), %занесение в базу данных
								  read_string(Inputfile, "\n", "\r", End, String),
								  split_string(String," ","", List),
								  child(Fid,Mid,Inputfile,List).

%если строка не подходит								  
child(Fid,Mid,Inputfile,[X,Y,Z]):- (X \= "1";
									Y \="CHIL";),!.
child(Fid,Mid,Inputfile,[X,Y]):-!.

%обработка строки вида "1 NAME ..."
name(Inputfile,[X,Y|T],_,N):- X="1", 
							  Y="NAME",
							  name_person(Inputfile,"",T,N),!.
					  
%если строка не подходит	
name(Inputfile,[X,Y|T],P,N):-
					 read_string(Inputfile, "\n", "\r", End, String),
					 split_string(String," ","", List),
					 name(Inputfile,List,0,N).

%получаем имя в виде строки
name_person(Inputfile,S,["//"],Res):- read_string(Inputfile, "\n", "\r", End, String),
									  split_string(String," ","", List),
									  marnm(Inputfile,List,S,Res),!. 
										
name_person(Inputfile,S,[H|T],N):- string_concat(S,H,Res),
								   string_concat(Res," ", N1),
								   name_person(Inputfile,N1,T,N),!. 
						
name_person(Inputfile,S,[],Res):- string_concat(S,"", Res).
		
%вспомогательный предикат для поиска строк вида "... _MARNM ..."
marnm(Inputfile,[A,B|Tail],S,Res):- B="_MARNM",
									name_person(Inputfile,S,Tail,Res),!.
									
marnm(Inputfile,[A,B|Tail],S,Res):- B\="_MARNM",
									B\="SEX",
									read_string(Inputfile, "\n", "\r", End, String),
									split_string(String," ","", List),
									marnm(Inputfile,List,S,Res),!. 
									
marnm(Inputfile,[A,B|Tail],S,Res):- B\="_MARNM",
									B="SEX",
									name_person(Inputfile,S,[],Res),!.

%предикат, описывающий двоюродного брата									
second_cousin(X, Y):-(parents(X,F,_);parents(X,_,F)),
					 (parents(F,G,_);parents(F,_,G)),
					  parents(G,Fg,M),
					  parents(B,Fg,M),
					  B\=G,
					 (parents(C,B,_);parents(C,_,B)),
					 (parents(Y,C,_);parents(Y,_,C)).
