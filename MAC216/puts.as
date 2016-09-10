        EXTERN puts
s       IS     $0
puts    SUBU   s,rSP,16 *Loads the first char addr in s
        LDOU   s,s,0
        SETW   rX,2
write   LDB    rY,s,0
        JZ     rY,end
        INT    #80
        ADDU   s,s,1  *Next char
        JMP    write
end     RET    1
