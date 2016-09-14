            EXTERN      main
c           IS          $0
spc         IS          $1
n           IS          $2
words       IS          $3
col         IS          $4
lenW        IS          $5
s           IS          $20

main        XOR         c,c,c           *c = 0
            XOR         n,n,n

            SUBU        rX,rSP,16
            LDOU        rX,rX,0
            SAVE        rSP,c,s
            PUSH        rX
            CALL        readnum
            REST        rSP,c,s
            OR          col,rA,0


            OR          words,rSP,0
            SETW        rX,1
start       INT         #80

limbo       JN          rA,just_word
            CALL        isSpace
            JNZ         spc,start       *If the char is space, go back to start
            PUSH        c
            STBU        rA,c,0          *M[c] <- rA (char)
            ADDU        c,c,1           *c++


read_word   INT         #80
            JN          rA,finish_w
            CALL        isSpace
            JNZ         spc,finish_w
            STBU        rA,c,0
            ADDU        c,c,1
            JMP         read_word

finish_w    XOR         rY,rY,rY
            STBU        rY,c,0
            ADDU        c,c,1
            ADDU        n,n,1
            JMP         limbo

*--------------CALLING WORD COUNT------------------------
*Calcula o tamanho de todas as palavras do texto
*ctz         IS          $7
*word_count  XOR         ctz,ctz,ctz
*pi          LDOU        s,words,ctz
*            SAVE        rSP,c,col
*            PUSH        s
*            CALL        len_word
*            REST        rSP,c,col
*            OR          lenW,rA,0       *lenW recebe o length
*            ADDU        ctz,ctz,8
*            ADDU        s,words,ctz
*            CMPU        s,s,rSP
*            JZ          s,print_words
*            JMP         pi
*------------FIM WORD COUNT-----------------------------

*------------------justify word-------------------------
just_word   SAVE        rSP,c,s
            PUSH        n            
            PUSH        words
            PUSH        col
            CALL        justify
            REST        rSP,c,s
            JMP         print_words












print_words XOR         s,s,s
            SETW        rX,2        *Print a "\n"
            SETW        rY,10
            INT         #80
print_loop  JZ          n,end
            SUBU        n,n,1
            SETW        rX,2
write       LDB         rY,s,0
            JZ          rY,cont
            INT         #80
            ADDU        s,s,1  *next char
            JMP         write
cont        SETW        rX,2        *Print a "\n"
            SETW        rY,10
            INT         #80
            ADDU        s,s,1
            JMP         print_loop
end         INT         0

*------------------Sub-rotina isSpace--------------------
isSpace     CMPU        rY,rA,10
            JZ          rY,space
            CMPU        rY,rA,32
            JZ          rY,space
            CMPU        rY,rA,9
            JZ          rY,space
            CMPU        rY,rA,13
            JZ          rY,space
            XOR         spc,spc,spc
            RET         0
space       SETW        spc,1
            RET         0
