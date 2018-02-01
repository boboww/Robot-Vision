#include <stdio.h>                          /* Sobel.c */
#include <math.h>
#include <stdlib.h>							//Original file didn't have this and atof gave warnings

int pic[256][256];							//Given values
int outpicx[256][256];
int outpicy[256][256];
int maskx[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
int masky[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}};
double ival[256][256], maxival;

int main(int argc, char **argv){			//Compiler gave warnings so cleaned line up
	int i, j, p, q, mr, sum1, sum2;
	double threshold1, threshold2;			//Added another threshold
	FILE *fp1, *fo1, *fo2, *fo3, *fopen();	
	char *foobar, throwaway[80];			//Added throwaway array for header fix
	
	argc--; argv++;
	foobar = *argv;							//Command line argument for the input file
	fp1 = fopen(foobar,"rb");				//Opens file in binary write mode

	fo1 = fopen("OutputMagni.pgm", "wb");	//Open file in binary write mode

    argc--; argv++;							
	foobar = *argv;							//Command line argument for 1st threshold value
	threshold1 = atof(foobar);				//Converts string input into double
	fo2=fopen("Threshold1.pgm", "wb");		//Creates 1st threshold image

	argc--; argv++;
	foobar = *argv;							//Command line argument for 2nd threshold value
	threshold2 = atof(foobar);				//Converts string input into double
	fo3=fopen("Threshold2.pgm", "wb");		//Creates 2nd threshold image
	
	fgets(throwaway, 80, fp1);				//Copied from pgmtoraw.c to fix headers
	fgets(throwaway, 80, fp1);				
	fgets(throwaway, 80, fp1);
	
	if (!((throwaway[0]=='2') && (throwaway[1]=='5') && (throwaway[2]=='5'))){
		fgets(throwaway, 80, fp1);			//Toss headers
	}
	
	for (i=0; i<256; i++){					//Given function
		for (j=0; j<256; j++){
			pic[i][j]  =  getc(fp1);
			pic[i][j]  &= 0377;
		}
	}	
	mr = 1;									//Prevents mask from being applied out of bounds
	
	for (i=mr; i<256-mr; i++){				//Applies mask
		for (j=mr; j<256-mr; j++){
			sum1 = 0;
			sum2 = 0;
			for (p=-mr; p<=mr; p++){
				for (q=-mr; q<=mr; q++){
					sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
					sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
				}
			}
			outpicx[i][j] = sum1;
			outpicy[i][j] = sum2;
		}
	}	
	maxival = 0;							//Maxival stores highes value of ival[i][j]
	
	for (i=mr; i<256-mr; i++){				//Given function
		for (j=mr; j<256-mr; j++){
			ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) + (outpicy[i][j]*outpicy[i][j])));
			if (ival[i][j] > maxival){
				maxival = ival[i][j];
			}
		}
	}
	
	fprintf(fo1, "P5\n256 256\n255\n");		//Adds header to output file
	
	for (i=0;i<256;i++){					//Prints magnitude map to output
		for (j=0;j<256;j++){
			ival[i][j] = (ival[i][j] / maxival) * 255;
			fprintf(fo1,"%c",(char)((int)(ival[i][j])));
		}
	}
	
	fprintf(fo2, "P5\n256 256\n255\n");		//Adds header to 1st threshold file
	fprintf(fo3, "P5\n256 256\n255\n");		//Adds header to 2nd threshold file
	
	for(i=0; i<256; i++){					//Prints thresholds to files
		for(j=0; j<256; j++){
			if(ival[i][j] > threshold1){	//1st Threshold
				fprintf(fo2, "%c", 255);
            }else{
				fprintf(fo2, "%c", 0);
            }if(ival[i][j] > threshold2){	//2nd Threshold
				fprintf(fo3, "%c", 255);
            }else{
				fprintf(fo3, "%c", 0);
			}
		}
	}
}