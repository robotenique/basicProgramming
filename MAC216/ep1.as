            EXTERN      main
c           IS          $0
spc         IS          $1
n           IS          $2
words       IS          $3
col         IS          $4
s           IS          $20

main        XOR         c,c,c           *c = 0
            XOR         n,n,n
            XOR         s,s,s

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

limbo       JN          rA,print_words
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

print_words SETW        rX,2
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

isSpace     CMPU        rY,rA,10
            JZ          rY,space
            CMPU        rY,rA,32
            JZ          rY,space
            XOR         spc,spc,spc
            RET         0
space       SETW        spc,1
            RET         0
