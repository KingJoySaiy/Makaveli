DATA SEGMENT
    WELCOME DB 10, "Welcome, please type in equations! (e.g. 2+5 or 6/4)",10,"$"
    ERROR_MSG DB 10,"Exit due error$"
    DIVISION_REMINDER_MSG DB " and remainder=$"
    INPUT DB 3 DUP('0')
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV DX,DATA ; DS指向数据段
    MOV DS,DX
    
    MOV AH,9    ; 输出WELCOME字符串
    MOV DX,OFFSET WELCOME
    INT 21H
    MOV BX,0

TAKE_INPUT:         ; 读取字符
    MOV AH,8        ; 读入一个字符
    INT 21H
    MOV CL,AL

    CMP BX,1        ; 第2个输入符需判断是否是运算符
    JE CHECK_CL_OPREATION

    CALL CHECK_CL_NUMBER ;第1和第3个数判断是否是数字
    CMP AL,1
    JE ASSIGN

    JMP ERROR_QUIT

CHECK_CL_OPREATION:    ; 判断CL是否是合法运算符
    CMP CL,'+'
    JE ASSIGN
    CMP CL,'-'
    JE ASSIGN
    CMP CL,'*'
    JE ASSIGN
    CMP CL,'/'
    JE ASSIGN
    JMP ERROR_QUIT

ASSIGN:     ; 将CL分配到数组中
    CALL PRINT_CL
    MOV INPUT[BX],CL
    INC BX
    CMP BX,3
    JNE TAKE_INPUT

CALCULATE_INPUT:    ; 计算结果
    MOV CL,INPUT[0]         ; 第一个数
    MOV BL,INPUT[1]         ; 操作符
    MOV CH,INPUT[2]         ; 第二个数
    CMP BL,'+'
    JE ADDITION
    CMP BL,'-'
    JE SUBTRACT
    CMP BL,'*'
    JE MULTIPLY
    CMP BL,'/'
    JE DIVIDE

ERROR_QUIT:     ; 错误退出
    MOV AH,9    ; 输出结束
    MOV DX,OFFSET ERROR_MSG 
    INT 21H
    MOV AH,4CH  ; 程序终止
    INT 21H
    
ADDITION:       ; 加法运算
    CALL PRINT_EQUAL_SIGN
    SUB CH,'0'
    ADD CL,CH
    MOV CH,'0' ; CH作为十位数值
    JMP CHECK_AND_PRINT_CX

SUBTRACT:       ; 减法运算
    CALL PRINT_EQUAL_SIGN
    SUB CH,'0'
    SUB CL,CH
    CALL CHECK_CL_NUMBER
    CMP AL,1
    JE PRINT_SUB    ; CL是数字则直接输出

    MOV BH,CL   ; 结果为负数
    MOV CL,'-'
    CALL PRINT_CL
    MOV CL,'9'+1     ; CL的相反数 = 10-(10+CL)
    ADD BH,10
    SUB BH,'0'      ; BH = CL+10-'0'
    SUB CL,BH
PRINT_SUB:  ; 输出减法结果
    CALL PRINT_CL
    JMP START

MULTIPLY:   ; 乘法运算
    CALL PRINT_EQUAL_SIGN
    SUB CH,'0'
    SUB CL,'0'
    MOV AL,CH
    MUL CL  ; AX = AL*CL
    MOV CL,AL
    MOV CH,AH
    ADD CL,'0'
    ADD CH,'0'
    CALL CHECK_AND_PRINT_CX
    
CHECK_AND_PRINT_CX: ; 判断CX合法并输出
    CALL CHECK_CL_NUMBER
    CMP AL,1
    JE PRINT_CX
    INC CH  ; 如果CL不是数字(结果大于等于10)，则CH进位，CL减10
    SUB CL,10
    JMP CHECK_AND_PRINT_CX

PRINT_CX:   ; 输出CX
    CMP CH,'0'
    JE PRINT_END
    MOV BH,CL ; BH临时存储个位数
    MOV CL,CH
    CALL PRINT_CL
    MOV CL,BH
PRINT_END:  ; 输出结束
    CALL PRINT_CL
    JMP START

DIVIDE:     ; 除法运算
    CALL PRINT_EQUAL_SIGN
    SUB CL,'0'                      ; TO USE THE REAL VALUE OF CL NOT '0'+VALUE
    SUB CH,'0'                     ; TO USE THE REAL VALUE OF CH NOT '0'+VALUE
    MOV AH,0                    ; CLEAR AH TO USE AX IN DIVISION
    MOV AL,CL
    MOV BL,CH
    DIV BL  ; AX = AL/BL
    MOV CH,AH
    MOV CL,AL
    ADD CL,'0'
    CALL PRINT_CL   ; 输出商
    MOV AH,9
    CMP CH,0
    JE QUIT_DIVISION
    MOV DX,OFFSET DIVISION_REMINDER_MSG ; 若余数不为0，则输出余数
    INT 21H     
    MOV CL,CH
    ADD CL,'0'
    CALL PRINT_CL
QUIT_DIVISION:
    JMP START

PRINT_EQUAL_SIGN:
    MOV AH,2
    MOV DL,'='
    INT 21H
    RET
    
PRINT_CL:   ; 输出CL
    MOV AH,2
    MOV DL,CL
    INT 21H
    RET

CHECK_CL_NUMBER: ; 判断CL是否是数字，是则AL置1，否则置0
    CMP CL,'0'
    JB NOT_NUMBER
    CMP CL,'9'
    JA NOT_NUMBER
    MOV AL,1
    RET
NOT_NUMBER: ; 非数字标记AL为0
    MOV AL,0
    RET

CODE ENDS
    END START
