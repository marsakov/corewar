.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live1_1, %1
		and r1, %0, r1

live1_1:	live %1
		zjmp %:live1_1
