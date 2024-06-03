(LOOP)
@24576
D=M
@HERE
D,JGT

@n
M=0
@8191
D=A
@max
M=D
(LOOP3)
@max
D=M
@n
D=D-M
@LOOP
D;JLT
@n
D=M
@16384
D=D+A
A=D
M=0
@n
M=M+1
@LOOP3
0;JMP

(HERE)
@n
M=0
@8191
D=A
@max
M=D
(LOOP2)
@max
D=M
@n
D=D-M
@LOOP
D;JLT
@n
D=M
@16384
D=D+A
A=D
M=-1
@n
M=M+1
@LOOP2
0;JMP





