program geraArvoreSintatica; // vamos trabalhar com um programa imperativo, usando lab

{
* E -> N | N + E | N - E | 
* E -> a | b | c
* }

uses crt;

var max,i: integer;

procedure gerarArvore(max: integer);
var wr,we,wd: integer;

begin
	if (max=1)
	then begin
			wr:= random(3);		// tenho 3 variáveis a b c 
			if (wr=0)
			then write('a')
			else if (wr=1)
				 then write('b')
				 else write('c');
		 end
	else if (max>=3)
		 then begin
				wr:= random(4);		// tenho 4 operadores + - * / 
				we:= random(3);		// tenho 3 variáveis a b c 
				wd:= random(3);		// tenho 3 variáveis a b c 
				max:= max - 2;
				
				if (wr=0) 				// +
				then if(we=0)			// a 
					 then write('a+') 
					 else if (we=1) 
						  then write('b+')
						  else write('c+');
						  
				if (wr=1) 				// -
				then if(we=0) 
					 then write('a-')
					 else if (we=1)
						  then write('b-')
						  else write('c-');
						  
				if (wr=2) 				// *
				then if(we=0)
					 then write('a*')
					 else if (we=1)
						  then write('b*')
						  else write('c*');

				if (wr=3) 				//  /
				then if(we=0)
					 then write('a/')
					 else if (we=1)
						  then write('b/')
						  else write('c/');

			if (max<>0)
			then gerarArvore(max);
		 end
    else writeln('erro');
end;

begin
	randomize;
	for i:= 1 to 10 do
		begin
			writeln;
			max:= random(5);
			if (max=0)
			then max:= 1
			else max:= 2 * max + 1;
			writeln('tamanho da árvore sintatdica desenhada = ', max);
			gerarArvore(max);
			writeln;
		end;
end.

