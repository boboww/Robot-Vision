*********************************USAGE*************************************
In a linux terminal run (without the >):
>make
>./a garb34.pgm .046

make = I have included a makefile. More info in notes.
./a = Standard linux command to run he program since I set the makefile to
		compile to just an "a" file.
garb34.pgm = Whichever .pgm you want to set the mask to. The root directory 
		has garb34.pgm.
.046 = percent

*If you recall for Assignment 1 I checked the MD5 of each output file and 
found them to match exactly, but in this case, I was only able to match the
first output magnitude image (from assignment 1) while the peaks and final
images look indistinguishable, but MD5 do not match given files. Might have
some differences in code, but I can't get them to be exact unfortunately.

*********************************OUTPUT************************************
"a" = Compiled program
"1magnitude.pgm" = File for low threshold
"2peaks.pgm" = File for high threshold
"3FinalEdges.pgm" = File for the magnitude function

Given comparison images are also in the folder starting with "canny" prefix
*********************************NOTES*************************************
As before, I included a generic makefile that I used for the program, and 
all you need is to run "make" in the command line to build the file. 
Basically the makefile uses a wildcard to compile all the .c files in the 
folder, so make sure there is only the single soble.c in the folder when 
compiling. The makefile includes some generic flags and reads as such when 
input:

gcc -g -Wall -Wextra -Wpedantic -o a sobel.c -lm

With the canny.c being a wildcard for whatever .c file is in the folder. 
Lots of warnings are useful for writing code from my experience, and -g 
makes it easy to debug with gdb (GNU debugger) when neccessary. I actually 
ran into a few segfaults while compiling when I messed up with command line
arguments.

********************************AFTERWORDS**********************************
So this assignment for me wasn't as perfect for me as assignment 1, which I 
managed to match exactly to MD5 hashes from output and given files. It's 
unfortunate but I ran out of time with everything going on, and I can only 
blame myself for that.

But anyways regarding the code, it wasn't as difficult as I imagined due 
to having most of the code in the lectures as actual code or pseudocode.

Did have some issues at first with the peak and final images coming out
looking a bit different than expected originally, but with some more tuning
I did get them to "look" the same as the provided files given by the prof.

Lots more to code this time around, but it was generally fun. Some confusion
with how to piece together certain parts, order, and some other usual minor
coding errors, but no major issues this time around. 

The percent I can understand if the value if off a bit, but the peaks one
should match the MD5 exactly. Still not certain why this happens.
****************************************************************************
