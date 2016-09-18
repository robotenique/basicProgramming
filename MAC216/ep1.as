            EXTERN      main
c           IS          $90
spc         IS          $91
n           IS          $92
words       IS          $93
col         IS          $94
barraN      IS          $95
aux         IS          $96
p           IS          $5
s           IS          $20

*----------------------------------- Leitura ----------------------------------------

main        XOR         p,p,p
            
            SUBU        rX,rSP,16       *Inicializa 'col'
            LDOU        rX,rX,0
            SAVE        rSP,c,s
            PUSH        rX
            CALL        readnum
            REST        rSP,c,s
            OR          col,rA,0


init        XOR         c,c,c           *c = 0
            XOR         n,n,n
            OR          words,rSP,0
            SETW        rX,1
start       INT         #80
limbo       JN          rA,just_word 
            CALL        isSpace
            JNZ         spc,start            
            JZ          c,cont_limbo
            JZ          barraN,cont_limbo2
            JMP        isP  *Então c!=0 e é um '\n'!
cont_limbo  JNZ         barraN,start
cont_limbo2 PUSH        c            
            STBU        rA,c,0
            OR          aux,rA,0
            ADDU        c,c,1

read_word   INT         #80
            JN          rA,finish_w
            CALL        isSpace
            JNZ         spc,finish_w
            JNZ         barraN,isP            
            STBU        rA,c,0
            OR          aux,rA,0
            ADDU        c,c,1
            JMP         read_word

finish_w    JZ          aux,backLimbo
            XOR         rY,rY,rY
            STBU        rY,c,0
            OR          aux,rY,0
            ADDU        c,c,1
            ADDU        n,n,1
 backLimbo  JMP         limbo


finish_w2   JZ          aux,finish_w2p
            XOR         rY,rY,rY           
            STBU        rY,c,0
            ADDU        c,c,1
            ADDU        n,n,1
finish_w2p  PUSH        c 
            STBU        rA,c,0
            ADDU        c,c,1
            OR          aux,rA,0            
            JMP         read_word

*----------------------------- desvio just_word -------------------------------------
*Envia parágrafo atual para o algoritmo de justificação imprimir.
just_word   OR          s,rA,0
            SAVE        rSP,c,barraN
            PUSH        n            
            PUSH        words
            PUSH        col
            CALL        justify
            REST        rSP,c,barraN
            SETW        rX,2
            SETW        rY,10
            INT         #80
            JN          s,end
            OR          col,rA,0            
            JMP         init

            INT         0

*-------------------- desvio isP (tratamento de parágrafos) -------------------------
isP         INT         #80            
            JN          rA,finish_w
            CALL        isSpace
            JNZ         spc,isP
            JZ          barraN,charIn_p            
            XOR         rY,rY,rY
            STBU        rY,c,0           
            ADDU        c,c,1

            JZ          aux,isP_1
            ADDU        n,n,1
isP_1       ADDU        p,p,1             *Achei 2 "\n",portanto é um parágrafo.                       
            JMP         just_word

charIn_p    JMP         finish_w2
*------------------- sub-rotina isSpace (detecta espaços e '\n') --------------------
isSpace     XOR         spc,spc,spc
            XOR         barraN,barraN,barraN
            CMPU        rY,rA,10            
            JZ          rY,isBarra
            CMPU        rY,rA,32
            JZ          rY,space
            CMPU        rY,rA,9
            JZ          rY,space
            CMPU        rY,rA,13
            JZ          rY,space            
            RET         0
space       SETW        spc,1
            RET         0
isBarra     SETW        barraN,1
            RET         0
*----------------------------------- Sub-rotina puts--------------------------------------------
*ARGS:  1 -(rSP-16) Endereço do primeiro char da palavra
*RETURN:0
str     IS     $0
puts    SUBU   str,rSP,16 *Loads the first char addr in s
        LDOU   str,str,0

        SETW   rX,2
write   LDB    rY,str,0
        JZ     rY,endp
        INT    #80
        ADDU   str,str,1  *Next char
        JMP    write
endp     RET    1


end         INT         0



