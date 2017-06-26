#########################################
# Veer Tatla cssc1153			#
# Josh Robey cssc1126			#
# CS570 Assignment 3			#
# Makefile				#
#					#
# This is make file for entire program. # 
#					#
#########################################
all:
	gcc -o aclock --std=gnu99 aclock.c
clean:
	rm aclock
run:
	./a3
