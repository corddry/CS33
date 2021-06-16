//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Jack Corddry
 * UCLA ID : 305413937
 * Email : jackcorddry@ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;

  for(i=0; i<DIM-1;i++)
  {
    super[i] += simple[i];
  }

  for(i=0; i<DIM-1;i++)
  {
    dot_product += super[i]*simple[i];
    
    moving_average = 0;
    for(ton=i;ton<DIM-1-WINDOW_SIZE;ton++)
    {
      moving_average += simple[ton];
    }
  }

  int a_secret = 5;
  fibonacci[0] = 1;
  fibonacci[1] = 1;

  for(i=2; i<DIM-1;i++)
  {
    fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
    if(i==3)
    {
      printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));
    }
  }

  step = 1.0 / NUM_STEPS;

//#pragma omp parallel for private(x) reduction(+:sum) UNCOMMENT LATER
  for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 

//#pragma omp parallel for private(x, y)
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= r*r) {
//#pragma omp critical
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2);

  long wntf = we_need_the_func();
  long gtf = gimmie_the_func();
  long boomba = wntf / gtf;
  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        aggregate+= old[i*DIM*DIM+j*DIM+k] * boomba;
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);

  int dimsq = DIM*DIM, newi = dimsq +DIM +1, val, end = DIM-1, tile = 8;
//#pragma omp parallel for private(newi, val, u) num_threads(8)
  for (i=1; i<end; i++) {
    //newi = i*dimsq + DIM + 1;
    for (j=1; j<end; j++) {
      for (k=1; k<end; k++) {
	newi++;//= i*DIM*DIM+j*DIM+k; 
        val=0;
        for (u=-1; u<=1; u++) {
          for (v=-1; v<=1; v++) {
	    /* val+=old[newi + u*dimsq + v*DIM +(k-1)]
	      + old[newi + u*dimsq + v*DIM +(k)]
	      + old[newi + u*dimsq + v*DIM +(k+1)]; */
/*

        
         + old[(i+u)*dimsq+(j+v)*DIM+(k)]
	        + old[(i+u)*dimsq+(j+v)*DIM+(k+1)];
	    */   
             val+=old[(i+u)*dimsq+(j+v)*DIM+(k-1)]
	            + old[(i+u)*dimsq+(j+v)*DIM+(k)]
		    + old[(i+u)*dimsq+(j+v)*DIM+(k+1)]; 
          }
        }
        val/=27;
	new[newi] = val;
	u=(val/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
	//newi++;
      }
    }
  }
/*
  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        
      }
      }
      }
*/
  
  return (double) (dot_product+moving_average+pi+pi2);


}
