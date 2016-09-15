            EXTERN      justify
cN          IS          $7      *Número da palavra atual
l           IS          $3      *Tamanho da palavra atual
cAddr       IS          $4      *Endereço da palavra atual
words       IS          $1      *Posição -> do stack <- que contém end. da palavra atual
inAdrr      IS          $6      *Posição -> do stack <- que contém end. da palavra inicial
n           IS          $0      *Número de palavras total
col         IS          $2      *Quantidade de colunas
aux         IS          $190         *Var. Auxiliar


justify     SUBU        rY,rSP,32       *Inicializa as variáveis
            LDOU        n,rY,0
            LDOU        words,rY,8
            LDOU        col,rY,16
            XOR         cN,cN,cN
            OR          inAdrr,words,0
            LDOU        cAddr,words,0

j_loop      CMPU        rY,cN,n         *Se (cN > n) -> finish_text
            JP          rY,finish_text
            SAVE        rSP,n,aux        *l <- tamanho(palavra)
            PUSH        cAddr
            CALL        len_word
            REST        rSP,n,aux
            OR          l,rA,0

            CMPU        rY,l,col        *Se l > col -> single_line
            JP          rY,single_line            
            JMP        normal_line      *Se l <= col -> normal_line

finish_text RET         0



*------------------desvio single_line --------------------
*Imprime uma única palavra + '\n'
single_line SAVE        rSP,n,aux     *Imprime palavra
            PUSH        cAddr
            CALL        puts
            REST        rSP,n,aux
            SETW        rX,2            *Imprime '\n'
            SETW        rY,10
            INT         #80
            ADDU        cN,cN,1         
            LDOU        cAddr,words,8
            ADDU        words,words,8
            JMP         j_loop          *Volta p/ j_loop

*------------------Sub-rotina normal_line -----------------
n_t         IS          $10          *Nº total de palavras
tc_l        IS          $11          *Total de caracteres de -> palavras <-
col_l       IS          $12          *Colunas 
cAddr_l     IS          $13          *Endereço da primeira palavra da linha
cN_l        IS          $14          *Nª da palavra atual
words_l     IS          $15          *Posição -> do stack <- que contém end. da palavra atual
cStk_l      IS          $16          *Posição -> do stack <-que contém end. da primeira palavra da linha
n_l         IS          $17          *Nº de palavras na linha
tc_lTemp    IS          $18          *Nª total de caracteres da linha


normal_line XOR         tc_lTemp,tc_lTemp,tc_lTemp
            OR          n_t,n,0
            OR          tc_l,l,0
            OR          col_l,col,0 
            OR          cAddr_l,cAddr,0
            OR          cN_l,cN,0
            OR          words_l,words,0
            OR          cStk_l,words_l,0
            OR          rX,cAddr_l,0  *private - import : rX é o ponteiro p/ o end. da palavra atual!!
            SETW        n_l,1
            
nl_loop     CMPU        rY,cN_l,n_t         *Se o nº da palavra atual > n total de palavras, vai para imprimir linha sem justificar            
            JZ          rY,last_line
            JP          rY,last_line            

            CMPU        rY,tc_lTemp,col_l
            JZ          rY,complete_nl      
            JP          rY,spcAlg_nl           
            ADDU        words_l,words_l,8
            LDOU        rX,words_l,0            *rX recebe end. da proxima palavra
           
           
            

            SAVE        rSP,n,aux        *Calcula len('palavra') e coloca em 'rA'
            PUSH        rX
            CALL        len_word
            REST        rSP,n,aux
            ADDU        tc_l,tc_l,rA
            OR          rY,n_l,0
            ADDU        n_l,n_l,1
            ADDU        tc_lTemp,tc_l,rY
            ADDU        cN_l,cN_l,1
            JMP         nl_loop

*------------------desvio complete_nl --------------------
*Imprime a linha com um espaço entre palavras
complete_nl XOR         aux,aux,aux
cl_loop     OR          rY,n_l,0            
            CMPU        rY,rY,aux
            JP          rY,cl_write 
            SETW        rX,2
            SETW        rY,10
            INT         #80           
            ADDU        cN,cN,n_l
            OR          cAddr,cAddr_l,0
            ADDU        words,words_l,8 
            OR          n,n_t,0
            OR          col,col_l,0
            JMP         j_loop
cl_write    ADDU        aux,aux,1
            SAVE        rSP,n,aux
            PUSH        cAddr_l
            CALL        puts
            REST        rSP,n,aux
            ADDU        cStk_l,cStk_l,8
            LDOU        cAddr_l,cStk_l,0
            CMPU        rY,n_l,aux
            JZ          rY,cl_loop 
            SETW        rX,2
            SETW        rY,32
            INT         #80
            JMP         cl_loop        

*------------------desvio spcAlg_nl  ---------------------
*'Desempilha' a última palavra, justifica e imprime a linha
temp        IS          $185         *Variável auxiliar (para loops)
spcAt       IS          $186         *Espaço atual da linha
spcO        IS          $187         *Espaços originais da linha
quoc        IS          $188         *Armazena o coeficiente da divisão
spcR        IS          $189         *Espaços que precisam ser distribuidos
spcAlg_nl   SUBU        rY,n_l,1
            ADDU        cN,cN,rY
            OR          cAddr,rX,0
            ADDU        words,words_l,0
            OR          n,n_t,0
            OR          col,col_l,0
            SAVE        rSP,n,aux 
            SUBU        n_l,n_l,1
            SUBU        tc_l,tc_l,rA
            SUBU        spcO,n_l,1
            SUBU        spcR,n_l,1
            ADDU        spcR,spcR,tc_l
            SUBU        spcR,col_l,spcR
            XOR         aux,aux,aux
            XOR         spcAt,spcAt,spcAt
            XOR         temp,temp,temp
            
            JZ          spcO,spc_single      *Se n_l == 1, imprime a palavra
            
            DIVU        quoc,spcR,spcO
            
spc_loop    OR          rY,n_l,0            
            CMPU        rY,rY,aux
            JP          rY,spc_write             
            SETW        rX,2
            SETW        rY,10
            INT         #80
            REST        rSP,n,aux
            JMP         j_loop

spc_single  SAVE        rSP,n,aux
            PUSH        cAddr_l
            CALL        puts
            REST        rSP,n,aux
            SETW        rX,2
            SETW        rY,10
            INT         #80
            REST        rSP,n,aux
            JMP         j_loop
           

spc_write   ADDU        aux,aux,1
            SAVE        rSP,n,aux
            PUSH        cAddr_l
            CALL        puts
            REST        rSP,n,aux
            ADDU        cStk_l,cStk_l,8
            LDOU        cAddr_l,cStk_l,0
            CMPU        rY,n_l,aux      *Se for a última palavra, volta para spc_loop
            JZ          rY,spc_loop
            ADDU        spcAt,spcAt,1
            ADDU        rZ,quoc,1
            XOR         temp,temp,temp
q_spc       CMPU        rY,rZ,temp      *q_spc: imprime (quoc + 1) espaços.
            JP          rY,qLoop_spc
            JMP         r_spc      
qLoop_spc   SETW        rX,2
            SETW        rY,32
            INT         #80
            ADDU        temp,temp,1
            JMP         q_spc            
r_spc       SUBU        rY,n_l,rR       *Se (n_l - rR) <= spcAt ,  imprime 1 espaço.            
            CMPU        rY,rY,spcAt
            JNP         rY,rWrite_spc
            JMP         spc_loop
rWrite_spc  SETW        rX,2
            SETW        rY,32
            INT         #80
            JMP         spc_loop



*------------------desvio last_line  ---------------------
*Imprime a última linha sem justificar, com um espaço entre palavras
last_line   SETW        aux,1
ll_loop     OR          rY,n_l,0            
            CMPU        rY,rY,aux
            JP          rY,ll_write 
            SETW        rX,2
            SETW        rY,10
            INT         #80           
            ADDU        cN,cN,n_l
            OR          cAddr,cAddr_l,0
            ADDU        words,words_l,8 
            OR          n,n_t,0
            OR          col,col_l,0
            JMP         j_loop
ll_write    ADDU        aux,aux,1
            SAVE        rSP,n,aux
            PUSH        cAddr_l
            CALL        puts
            REST        rSP,n,aux
            ADDU        cStk_l,cStk_l,8
            LDOU        cAddr_l,cStk_l,0
            CMPU        rY,n_l,aux
            JZ          rY,ll_loop 
            SETW        rX,2
            SETW        rY,32
            INT         #80
            JMP         ll_loop        
end_nl      RET 0




*------------------Sub-rotina len_word--------------------
*ARGS:  1 -(rSP-16) Endereço do primeiro char da palavra
*RETURN:1 -(rA)     Tamanho da palavra
iAddr       IS          $0
cmpr        IS          $1
i           IS          $2
len_word    SUBU        iAddr,rSP,16
            LDOU        iAddr,iAddr,0

            XOR         i,i,i
l_loop      LDBU        cmpr,iAddr,0
            JZ          cmpr,endj
            ADDU        i,i,1
            ADDU        iAddr,iAddr,1
            JMP         l_loop
endj        OR          rA,i,0
            RET         1

*----------------Sub-rotina puts--------------------------
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
