#include <stdio.h>                          	/* Canny.c */
#include <math.h>
#include <stdlib.h>								//Original file didn't have this and atof gave warnings

#define  PICSIZE 256
#define  MAXMASK 100

int    pic[PICSIZE][PICSIZE];					//Merged marrh.c and sobel.c
double outpicx[PICSIZE][PICSIZE];				//global variables
double outpicy[PICSIZE][PICSIZE];
double outpic2[PICSIZE][PICSIZE];
double xmask[MAXMASK][MAXMASK];
double ymask[MAXMASK][MAXMASK];
double xconv[PICSIZE][PICSIZE];
double yconv[PICSIZE][PICSIZE];
double edgeflag[PICSIZE][PICSIZE];
double ival[PICSIZE][PICSIZE];
double final[PICSIZE][PICSIZE];
double histogram[PICSIZE];

int main(int argc, char **argv){				//Compiler gave warnings so cleaned line up
	int     i, j, p, q, mr, cutOff, areaOfTops;
	int 	centx, centy, test = 1, HI, LO;		//more from marrh.c
	double  sig = 1.0, maxival, maxivalnew;
	double 	slope, percent;						//more from marrh.c
	double 	xmaskval, ymaskval, sumx, sumy;		//extras added
    FILE    *fo1, *fo2, *fo3;
	FILE	*fp1, *fopen();					
	char 	*foobar, throwaway[80];				//Added throwaway array for header fix
		
	argc--; argv++;
	foobar = *argv;								
	fp1 = fopen(foobar,"rb");					//Opens file in binary write mode
	
	argc--; argv++;
	foobar = *argv;	
	percent = atof(foobar);						//Converts string input into double

	argc--; argv++;							
	foobar = *argv;								
	fo1 = fopen("1magnitude.pgm", "wb");		//Create 1st magnitude image

    argc--; argv++;							
	foobar = *argv;								
	fo2=fopen("2peaks.pgm", "wb");				//Creates 2nd peaks image

	argc--; argv++;
	foobar = *argv;								
	fo3=fopen("3FinalEdges.pgm", "wb");			//Creates 3rd and final image
	
	mr = (int)(sig * 3);						//from marrh.c

	centx = (MAXMASK / 2);						//marrh.c
	centy = (MAXMASK / 2);						//marrh.c
	
	fgets(throwaway, 80, fp1);					//Copied from pgmtoraw.c to fix headers
	fgets(throwaway, 80, fp1);				
	fgets(throwaway, 80, fp1);
	
	if (!((throwaway[0]=='2') && (throwaway[1]=='5') && (throwaway[2]=='5'))){
		fgets(throwaway, 80, fp1);				//Toss headers
	}
	
	for (i = 0; i < 256; i++){					//Given function
		for (j = 0; j < 256; j++){				//Stores images
			pic[i][j]  =  getc(fp1);
			pic[i][j]  &= 0377;
		}
	}	
	
	for (p = -mr; p <= mr; p++){				//Part 1 Gradient Magnitude
		for (q = -mr; q <= mr; q++){			//Get derivatives for X and Y
			xmaskval = (-q ) * (exp(-1*(((p*p)+(q*q))/(2*(sig*sig)))));
			ymaskval = (-p ) * (exp(-1*(((p*p)+(q*q))/(2*(sig*sig)))));
			
			xmask[p+centy][q+centx] = xmaskval;
			ymask[p+centy][q+centx] = ymaskval;
		}
	}	

	for (i = mr; i <= 255-mr; i++){				//Still Part 1
		for (j = mr; j <= 255-mr; j++){			//Use convolution
			sumx = 0;
			sumy = 0;
			
			for (p = -mr; p <= mr; p++){		//Modified from marrh.c
				for (q = -mr; q <= mr; q++){	//and sobel.c
					sumx += pic[i+p][j+q] * xmask[p+centy][q+centx];
					sumy += pic[i+p][j+q] * ymask[p+centy][q+centx];
				}
			}			
			outpicx[i][j] = sumx;
			outpicy[i][j] = sumy;
			xconv[i][j] = sumx;
			yconv[i][j] = sumy;
		}
	}
	
	maxival = 0;								//Maxival stores highes value of ival[i][j]
		
	for (i = mr; i < 256-mr; i++){				//Modified function for magnitude/sqrt
		for (j = mr; j < 256-mr; j++){
			ival[i][j]=sqrt((double)((outpicx[i][j]*outpicx[i][j]) + 
						(outpicy[i][j]*outpicy[i][j])));
			if (ival[i][j] > maxival){
				maxival = ival[i][j];
			}
		}
	}
	
	maxivalnew = 0;
	
	fprintf(fo1, "P5\n256 256\n255\n");			//Adds header to fo1
	
	for (i = 0; i < 256; i++){					//Print to fo1 for magnitude
		for (j = 0; j < 256; j++){
			ival[i][j] = (ival[i][j] / maxival) * 255;
			
			if(ival[i][j] > maxivalnew){
				maxivalnew = ival[i][j];
			}
            fprintf(fo1, "%c", (char)((int)(ival[i][j])));
        }
    }
	
	for(i = mr; i < 256-mr; i++){				//Part 2 Compute Peaks
		for(j = mr; j < 256-mr; j++){			//Directional gradient
			if(xconv[i][j] == 0.0){				//From video for Peaks
				xconv[i][j] = 0.00001;
			}
			slope = yconv[i][j]/xconv[i][j];
			
			if((slope <= .4142)&&(slope > -.4142)){
				if((ival[i][j] > ival[i][j-1])&&(ival[i][j] > ival[i][j+1])){
					edgeflag[i][j] = 255;
				}
			}else if((slope <= 2.4142)&&(slope > .4142)){
				if((ival[i][j] > ival[i-1][j-1])&&(ival[i][j] >ival[i+1][j+1])){
					edgeflag[i][j] = 255;
				}
			}else if((slope <= -.4142)&&(slope > -2.4142)){
				if((ival[i][j] > ival[i+1][j-1])&&(ival[i][j] > ival[i-1][j+1])){
					edgeflag[i][j] = 255;
				}
			}else if((ival[i][j] > ival[i-1][j])&&(ival[i][j] > ival[i+1][j])){
				edgeflag[i][j] = 255;
			}
		}
	}	
	
	fprintf(fo2, "P5\n256 256\n255\n");			//Adds header to fo2
	
	for (i = 0; i < 256; i++){ 
		for (j = 0; j < 256; j++){
			fprintf(fo2,"%c",(char)((int)(edgeflag[i][j])));
		}
	}
	
	for (i = mr; i < 256-mr; i++){				//Part 4 Auto Compute HI and LOW
		for (j = mr;j < 256-mr; j++){
			histogram[(int)ival[i][j]]++;		//Modified from slide pseudocode
        }
    }
	
	cutOff = percent * PICSIZE * PICSIZE;		//More from pseudocode
	areaOfTops = 0;
	
	for (i = PICSIZE; i >= 1; i--){				//Pseudocode from slides
		areaOfTops += histogram[i];
		
		if (areaOfTops > cutOff){				//Converted to actual code
			break;
		}
		HI = i;
	}		
	LO = 0.35*HI;
	
	for(i = 0; i < 256; i++){					//Part 3 Double Threshold
		for(j = 0; j < 256; j++){				//New grid of zeros
			final[i][j] = 0;
		}
	}
	
	for(i = 0; i < 256; i++){
		for(j = 0; j < 256; j++){
			if(edgeflag[i][j] == 255){			//Check for peaks
				if(ival[i][j] > HI){			//Check if magnitude > high
					final[i][j] = 255;
					edgeflag[i][j] = 0;
				}else if(ival[i][j] < LO){		//Check if magnitude < low
					edgeflag[i][j] = 0;
					final[i][j] = 0;
				}
			}
		}
	}
	
	while(test){								//This part is just a mess
		test = 0;								//was slightly annoying
		
		for(i = 0; i < 256; i++){
			for(j = 0; j < 256; j++){
				if(edgeflag[i][j] == 255){
					for(p = -1; p <= 1; p++){
						for(q = -1; q <= 1; q++){
							if(final[i+p][j+q] == 255){
								final[i][j] = 255;
								edgeflag[i][j] = 0;
								test = 1;
							}
						}
					}
				}
			}
		}
	}
	
	fprintf(fo3, "P5\n256 256\n255\n");			//Adds header to fo3
	
	for (i = 0; i < 256; i++){					//Print to fo3 for final
		for (j = 0; j < 256; j++){
			if(final[i][j] == 255){
				fprintf(fo3, "%c", (char)((int)(final[i][j])));
			}else{
				final[i][j] = 0;
				fprintf(fo3, "%c", (char)((int)(final[i][j])));
            }
        }
    }
}