DATA SEGMENT
 PORTA EQU 00H
 PORTB EQU 02H
 PORTC EQU 04H
 PORT_CON EQU 06H
 
DATA ENDS

CODE SEGMENT

 MOV AX, DATA
 MOV DS, AX	; Put the data segment we created above in the data segment register.

ORG 0000H	;this sets the starting(originating) address of our code in the memory.

START:
 MOV DX, PORT_CON		;to select command register or to configure ports.
 MOV AL, 10000010B	;this number identifies the i/o function of ports A,B and C (D7D6D5D4D3D2D1D0)
			;D4 -- i/o of PortA
			;D1 -- i/o of PortB
			;D0 -- i/o of LowerPortC
			;D3 -- i/o of UpperPortC
 OUT DX, AL	;to confifure ports as i/o as reqd.
 MOV CX, 3	;CX to contain the no of digits.
 JMP XX
XX:
 MOV AL, 0H
 MOV DX, PORTB
 IN AL, DX


 CMP AL, 0001B
 JE AMMAR
 CMP AL, 0011B
 JE UZAIR
 CMP AL, 0111B
 JE HASNAIN
 CMP AL, 1111B
 JE GHULAM

JMP XX
 
AMMAR:
	MOV BL, 100	;bit sequence for leftmost digit.
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00100100B	;binary code for two
	OUT PORTA, AL		;to display two
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00011001B	;binary code for zero
	OUT PORTA, AL		;to display zero
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 11000000B	;binary code for Seven
	OUT PORTA, AL		;to display Seven
	CALL DELAY
	JMP XX

UZAIR:
	MOV BL, 100	;bit sequence for leftmost digit.
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 01111001B	;binary code for one
	OUT PORTA, AL		;to display one
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00010000B	;binary code for nine
	OUT PORTA, AL		;to display nine
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00010000B	;binary code for nine
	OUT PORTA, AL		;to display nine
	CALL DELAY
	JMP XX

HASNAIN:
	MOV BL, 100	;bit sequence for leftmost digit.
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00100100B	;binary code for two
	OUT PORTA, AL		;to display two
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 11000000B	;binary code for zero
	OUT PORTA, AL		;to display zero
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00000010B	;binary code for six
	OUT PORTA, AL		;to display six
	CALL DELAY
	JMP XX

GHULAM:
	MOV BL, 100	;bit sequence for leftmost digit.
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00100100B	;binary code for two
	OUT PORTA, AL		;to display two
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00110000B	;binary code for three
	OUT PORTA, AL		;to display three
	CALL DELAY
	
	ROR BL,1		;activate next digit
	MOV AL, BL
	OUT PORTC, AL	;turn on the digit acc to the bit sequence.
	MOV AL, 00000010B	;binary code for six
	OUT PORTA, AL		;to display six
	CALL DELAY
	JMP XX
	



JMP XX
DELAY PROC NEAR		;delay loop
	MOV DX, 300
BACK:	DEC DX
	JNZ BACK
	RET
	DELAY ENDP



CODE ENDS
END