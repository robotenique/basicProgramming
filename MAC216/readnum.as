        EXTERN      readnum
n       IS          $0
cmpr    IS          $1
ad      IS          $2
c       IS          $3
ch      IS          $4
readnum XOR         n,n,n
        XOR         c,c,c
        SUBU        ad,rSP,16
        LDOU        ad,ad,0

read    LDBU        ch,ad,c
        CMP         cmpr,ch,48
        JN          cmpr,finish
        CMP         cmpr,ch,57
        JP          cmpr,finish
        SUBU        ch,ch,48
        MULU        n,n,10
        ADDU        n,n,ch
        ADDU        c,c,1
        JMP         read

finish  OR          rA,n,0
        RET         1