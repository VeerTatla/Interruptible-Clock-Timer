README.md
CS570 Assignment 3
Veerparatap Tatla cssc1153
Josh Robey cssc1126
CS570 Operating Systems, Summer 2017
Assignment #3: Design and Management of an interruptable, clock, and timer

*TESTING* use Veer Tatla class account cssc1153 for testing!

File Manifest:
1.) aclock.c -----> Main program that does work for clock and timer.
2.) aclock.h------> Contains headers for aclock.c
3.) Makefile----> Automates process for compiling program. 
4.) README.md---> Has all information about program.

Compile and run instructions:
At the command line to compile type-
$ make
Then to run executable simply type-
For default timer of 30 seconds
$ aclock
OR
For custom timer in seconds
$ aclock time(s) 

Lessons learned:

We learned a lot about how to implement clocks and timers. We 
struggled to get the alarm function working and i believe that is 
because using the pipe method got complicated. I think we s
hould have use signal to maintain simplicity.
