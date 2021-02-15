.name "Party"
.comment "DON’T GIVE UP"

	live %1
	fork %-10
	live %1
	fork %-10
	live %1
	fork %-10
	live %1
	fork %-10
	xor r2, r3, r4
live:	st r1, 6
	live %1
	fork %500
	zjmp %:live
