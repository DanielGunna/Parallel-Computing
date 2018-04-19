/*
 * Copyright(C) 2014 Alyson D. Pereira <alyson.deives@outlook.com>, 
 *                   Pedro H. Penna <pedrohenriquepenna@gmail.com>
 * 
 * fast.c - FAST corner detection kernel.
 */

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "fast.h"

__global__ isEdge ( int *in, int n, int howmany ){

	int index = threadIdx.x + BlockIdx.x * BlockDim.x;
	
	__shared__ int isResp = 0;
	int countHigher;
	int countLower;
	if ( index < n ){
		for ( int i = howmany; i > 0; i--)}{
			if ( i - howmany > 0 ){
				int test = in[i-howmany]
				if ( test > in[index] ) countHigher++;
				if ( test < in[index] ) countLower++;
			}
		}
	}
	//se tiver todos os necessarios
	if ( countLower == howmany || countHigher == howmany){
		out = 1; //qq thread que tiver, ja faz o ponto em questao thread
	}
}
/*
 * FAST corner detection.
 */
 
int fast(char *img, int imgsize, int *mask)
{
	int i,j,k,r,z,x,y;
	char accumBrighter, accumDarker;
	char imagePixel,centralPixel;
	int numcorners = 0;
	
	for (j = 0; j< imgsize; j++){
	  for (i = 0; i< imgsize; i++){
	    centralPixel = img[j*imgsize + i];
	    z = 0;
	    while(z<16){
	      accumBrighter = 0;
	      accumDarker = 0;
	      for(r = 0;r<12;r++){
		x = i + mask[((r+z) * 2) + 0];
		y = j + mask[((r+z) * 2) + 1];

		if(x >=0 && y>=0 && ((y * imgsize + x) < (imgsize*imgsize))){
		  imagePixel = img[y * imgsize + x];
		  if(imagePixel >= (centralPixel+THRESHOLD)){
		    if(accumBrighter == 0){
		      accumDarker++;
		    }
		    else{
		      z += r - 1;
		      goto not_a_corner;
		    }
		  }
		  else if (imagePixel<=(centralPixel-THRESHOLD)){
		    if(accumDarker == 0){
		      accumBrighter++;
		    }
		    else{
		      z += r - 1;
		      goto not_a_corner;
		    }
		  }
		  else{
		    z += r;
		    goto not_a_corner;
		  }
		}
	      }
	      if(accumBrighter == 12 || accumDarker == 12){
		numcorners++;
		z = 16;
	      }
	    not_a_corner:			z++;
	    }
	  }
	}
	
	
	return numcorners;
}
