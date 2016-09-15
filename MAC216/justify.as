            EXTERN      justify
n           IS          $0      *Número de palavras total
words       IS          $1      *Posição -> do stack <- que contém end. da palavra atual
col         IS          $2      *Quantidade de colunas
l           IS          $3      *Tamanho da palavra
cAddr       IS          $4      *Endereço da palavra atual
inL         IS          $5      *Endereço anterior
inAdrr      IS          $6      *Posição -> do stack <- que contém end. da palavra inicial
cN          IS          $7      *Tamanho da palavra atual
justify     SUBU        rY,rSP,32
            LDOU        n,rY,0
            LDOU        words,rY,8
            LDOU        col,rY,16
            XOR         cN,cN,cN
            OR          inAdrr,words,0
            LDOU        cAddr,words,0

j_loop      CMPU        rY,cN,n         *Se o nº da palavra atual > n total de palavras, vai para finish_text
            JP          rY,finish_text
            SAVE        rSP,n,cN        *Calcula len('palavra') e coloca em 'l'
            PUSH        cAddr
            CALL        len_word
            REST        rSP,n,cN
            OR          l,rA,0

            CMPU        rY,l,col        *Se len('palavra') > col , chama single_line
            JP          rY,single_line
            
            CALL        normal_line
finish_text INT         0


            RET         0



*------------------desvio single_line --------------------
*Imprime uma única palavra + '\n'
single_line SAVE        rSP,n,cN
            PUSH        cAddr
            CALL        puts
            REST        rSP,n,cN
            SETW        rX,2
            SETW        rY,10
            INT         #80
            ADDU        cN,cN,1     *cN++
            LDOU        cAddr,words,8
            ADDU        words,words,8
            JMP         j_loop

*------------------Sub-rotina normal_line -----------------
n_t         IS          $10          *Nº total de palavras
tc_l        IS          $11          *Total de caracteres de -> palavras <-
col_l       IS          $12          *Colunas 
cAddr_l     IS          $13          *Endereço da palavra atual
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
            JP          rY,end_nl
            CMPU        rY,tc_lTemp,col_l
            JZ          rY,complete_nl      
            JP          rY,spcAlg_nl           *do: Desempilha a última palavra e manda para distribuir espaços (->j_loop)
            ADDU        words_l,words_l,8
            LDOU        rX,words_l,0                *rX recebe end. da proxima palavra
           
           
            

            SAVE        rSP,n_t,tc_lTemp        *Calcula len('palavra') e coloca em 'rA'
            PUSH        rX
            CALL        len_word
            REST        rSP,n_t,tc_lTemp
            ADDU        tc_l,tc_l,rA
            OR          rY,n_l,0
            ADDU        n_l,n_l,1
            ADDU        tc_lTemp,tc_l,rY
            ADDU        cN_l,cN_l,1
            JMP         nl_loop

*------------------desvio complete_nl --------------------
*Imprime a linha com um espaço entre palavras
aux         IS          $190         *Var. Auxiliar
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
            SAVE        rSP,n_t,aux
            PUSH        cAddr_l
            CALL        puts
            REST        rSP,n_t,aux
            ADDU        cStk_l,cStk_l,8
            LDOU        cAddr_l,cStk_l,0
            CMPU        rY,n_l,aux
            JZ          rY,cl_loop 
            SETW        rX,2
            SETW        rY,32
            INT         #80
            JMP         cl_loop        

*------------------desvio spcAlg_nl  ---------------------
*'Desempilha' a última palavra, justifica a linha e imprime
spcO        IS          $16         *Espaços originais da linha
quoc        IS          $17         *Armazena o coeficiente da divisão
spcR        IS          $190        *Espaços que precisam ser distribuidos
spcAlg_nl   ADDU        cN,cN,n_l
            OR          cAddr,rX,0
            ADDU        words,words_l,0
            OR          n,n_t,0
            OR          col,col_l,0            
            SUBU        n_l,n_l,1
            SUBU        tc_l,tc_l,rA
            SUBU        spcO,n_l,1
            SUBU        spcR,n_l,1
            ADDU        spcR,spcR,tc_l
            SUBU        spcR,col_l,spcR
            XOR         aux,aux,aux
            
            JZ          spcO,end_nl      *do do do : VERIFICAR CASO QUANDO spcO == 0 (significa que n_l == 1)
            
            DIVU        q,spcR,spcO
spc_write   ADDU        aux,aux,1
            SAVE        rSP,n_t,aux
            PUSH        cAddr_l
            CALL        puts
            REST        rSP,n_t,aux
            ADDU        cStk_l,cStk_l,8
            LDOU        cAddr_l,cStk_l,0
            CMPU        rY,n_l,aux
            JZ          rY,cl_loop 
            SETW        rX,2
            SETW        rY,32
            INT         #80
            JMP         cl_loop




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
