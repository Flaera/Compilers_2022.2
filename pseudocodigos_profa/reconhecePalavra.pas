{Autômatos de reconhecimento de linguagens regulares

G1=([qo,q1,qf],[a,b,c],P,q0), onde P é
q0    ::= aq0 | bq0 | cq1       (estado inicial)
q1    ::= cqf | aq0 | bq0
qf    ::= aqf | bqf | cqf       (estado final)
}

program autoGoto1; // vamos trabalhar com um programa imperativo, usando label

uses crt;

const fim = '0';     // constante para marcar o fim da cadeia lida

 var s:string;         // cadeia lida
 var p:integer;        // posição de um símbolo na cadeia

 procedure lePalavra;
 begin
    p :=1;
    s := 'ccabcba0'; {cadeia a ser reconhecida}
 end;

 function xp(c: char):boolean;   
 begin
    If s[p]=c
    Then xp := true
    Else xp := false;
 end;
 
 function np :boolean;
 begin
    p  := p+1;
    np := true;
 end;

 label q0, q1, qf,qe;         // cada label vai corresponder a um estado
 var i,max :integer;

 begin
 lePalavra;
 max := length(s);
 
 for i := 0 to max do
    begin
        p:=1;
        goto q0;

// q0    ::= aq0 | bq0 | cq1       (estado inicial)
            q0:  If xp('a') and np
                 Then goto q0
                 Else If xp('b') and np
                         Then goto q0
                         Else 	If xp('c') and np
								Then goto q1
								Else goto qe;  // estado para informar o erro

// q1    ::= cqf | aq0 | bq0
            q1:  If xp('c') and np
                   Then goto qf
                   Else If xp('a') and np
                           Then goto q0
                           Else 	If xp('b') and np
									Then goto q0
									Else goto qe;  // estado para informar o erro

// qf    ::= aqf | bqf             (estado final)
            qf:  If xp('a') and np
                   Then goto qf
                   Else If xp('b') and np
                           Then goto qf
                           Else 	If xp('c') and np
									Then goto qf
									Else If xp(fim) and np
									Then begin
                                          writeln('Cadeia reconhecida!');
                                          exit;
                                        end  
									Else goto qe;  //estado para informar o erro

// este estado deve ser trabalhado por vocês
            qe:  begin
                   writeln('Cadeia não reconhecida na posicao: ', p);
                   exit;
                 end; 
	end;
end.

