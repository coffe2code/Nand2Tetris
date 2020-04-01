// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.


(LOOP1)
	@24576
	D = M
	@END1
	D;	JEQ


	@16384
	D = A
	@R0
	M = D

	(LOOP2)
		@R0
		D = M
		@24575
		D = D - A;
		@END2
		D; JGT

		@R0
		A = M
		M = -1
		@R0
		M = M + 1 


	(END2)
	@LOOP2
	0;	JMP


(END1)
	@16384
	D = A
	@R0
	M = D
	(LOOP3)
		@R0
		D = M
		@24575
		D = D - A
		@END3
		D; JGT

		@R0
		D = M
		@D
		M = 0
		@R0
		M = M + 1

	(END3)
	@LOOP1
	0; JMP