            EXTERN      main
c           IS          $90
spc         IS          $91
n           IS          $92
words       IS          $93
col         IS          $94
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


*------------------justify word-------------------------
just_word   INT         #DB5C5C *n, words, col
            INT         #DB5D5D
            INT         #DB5E5E
            SAVE        rSP,c,$190
            PUSH        n            
            PUSH        words
            PUSH        col
            CALL        justify
            REST        rSP,c,$190            
            OR          n,$0,0
            OR          words,$6,0
            OR          col,$2,0
            INT         #DB5C5C *n, words, col
            INT         #DB5D5D
            INT         #DB5E5E
            INT         0

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
