(SimpleFunction.test)
@SP
A=M
M=0
@SP
M=M+1
@SP
A=M
M=0
@SP
M=M+1
@0
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@LCL
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
D=D+M
M=D
@SP
M=M-1
@SP
A=M-1
M=!M
@0
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
D=D+M
M=D
@SP
M=M-1
@1
D=A
@ARG
A=D+M
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
A=A-1
D=M-D
M=D
@SP
M=M-1
//Set FRAME = LCL
@LCL
D=M
@13
M=D
//Set RET = *(FRAME-5)
@13
D=M
@5
D=D-A
A=D
D=M
@14
M=D
//Set arg=pop()
@SP
A=M-1
D=M
@ARG
A=M
M=D
@SP
M=M-1
//Set SP = ARG+1
@ARG
D=M+1
@SP
M=D
//Set THAT = *(frame-1)
@13
A=M-1
D=M
@THAT
M=D
//Set THIS = *(frame-2)
@2
D=A
@13
A=M
A=A-D
D=M
@THIS
M=D
//Set ARG = *(frame-3)
@3
D=A
@13
A=M
A=A-D
D=M
@ARG
M=D
//Set LCL = *(frame-4)
@4
D=A
@13
A=M
A=A-D
D=M
@LCL
M=D
//goto ret
@14
A=M
0;JMP
(END)
@END
0;JMP