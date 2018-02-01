*********************************USAGE*************************************
Using a linux terminal run:
make
./a garb34.pgm 40 110

make = I have included a makefile. More info in notes.
./a = Standard linux command to run he program since I set the makefile to
		compile to just an "a" file.
garb34.pgm = Whichever .pgm you want to set the mask to. The root directory 
		has face05.gpm and garb34.pgm. Rest are in folder \Input Images
40 = Threshold 1
110 = Threshold 2

*I already check the MD5 hashes of my generated files and the provided
comparison ones, and all three are identical with thresholds of 40 and 110.

*********************************OUTPUT************************************
"a" = Compiled program
"LowThreshold.pgm" = File for low threshold
"HighThreshold.pgm" = File for high threshold
"OutputMagni.pgm" = File for the magnitude function

*********************************NOTES*************************************
So it didn't look like there was too much to program for this assignment,
which was good since it's been a while since I last had a programming class
I included a generic makefile that I used for the program, and all you need 
is to run "make" in the command line to build the file. Basically the 
makefile uses a wildcard to compile all the .c files in the folder, so make 
sure there is only the single soble.c in the folder when compiling. The 
makefile includes some generic flags and reads as such when input:

gcc -g -Wall -Wextra -Wpedantic -o a sobel.c -lm

With the sobel.c being a wildcard for whatever .c file is in the folder. 
Lots of warnings are useful for writing code from my experience, and -g 
makes it easy to debug with gdb (GNU debugger) when neccessary. I actually 
ran into a few segfaults while compiling when I messed up with command line
arguments.

********************************AFTERWORDS**********************************
There was another argument in the original sobel.c which looked it was used
to set the output file, but in my modified code I just set that to 
OutputMagni.pgm for simplicity. Not neccessary to have more arguments that 
aren't needed. Make sure there is no argument to set the output file when 
running my program. 

Also, no error messages, so make sure the program is executed exactly as 
described here. 

In the irfanviewAndPGM.docx, there was a question: 
"The output file should be about 65551 in size (why is it this size??)."
-256x256 = 65536 (each pixel = 1 byte) and then add some more for the header
****************************************************************************
