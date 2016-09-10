        EXTERN      putnum
n       IS          $0
p       IS          $1
calc    IS          $2
putnum  SUBU        n,rSP,16
        LDOU        n,n,0   *$n <- M[$n]
        SETW        p,1
        OR          calc,n,0
        DIVU        calc,calc,10
verf    JZ          calc,print
        DIVU        calc,calc,10
        MULU        p,p,10
verf2   JMP         verf
print   SETW        rX,2
        JZ          p,end
        DIVU        calc,n,p
        DIVU        calc,calc,10
        ADDU        rY,rR,48
        INT         #80
        DIVU        p,p,10
        JMP         verf2
end     RET         1
