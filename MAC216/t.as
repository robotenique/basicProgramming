            EXTERN      main
c           IS          $0
main        SUBU        rX,rSP,16
            LDOU        rX,rX,0
            PUSH        rX
            CALL        readnum
            OR          c,rA,0
            INT         #DB0000
            INT         0
