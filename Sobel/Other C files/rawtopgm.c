/* usage:   rawtopgm  totalrows totalcolumns inputfilename > filename.pgm */

#include <stdio.h>

int main (int argc, char **argv){
	int     i, j, rows, cols ;
	FILE    *fp1, *fo1, *fo2, *fopen();
	char    ci, *foobar;
	
	argc--; argv++;
	foobar = *argv;
	rows = atoi(foobar);
	
	argc--; argv++;
	foobar = *argv;
	cols = atoi(foobar);
	
	argc--; argv++;
	foobar = *argv;
	fp1 = fopen(foobar,"rb");
	
	printf("P5\n");
	printf("%d %d\n", rows, cols);
	printf("255\n");
	
	for (i=0; i<rows; i++){
		for (j=0; j<cols; j++){
			ci = getc(fp1);
			printf("%c", ci);
		}
	}
}
