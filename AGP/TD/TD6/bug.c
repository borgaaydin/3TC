/* bug.c, source:  Christian NGUYEN */

#include <stdio.h>
#include <stdlib.h>

void place( int *t, int i, int j)
{
  t [ i ] =  j;
  printf("%d\n", t[i]);
}

void traitement( int  n )
{ int *t;
  unsigned int i = 0;
  t = (int*) malloc(n * sizeof(int));
  for( i = n-1; i >= 0 ; i--)
      place( t, i  , i*i ) ;
  free( t );
}

int main ( int argc, char *argv[] )
{ int n;
  
  n = atoi( argv[1] );

  printf("\nbug du -1 %d\n",n);

  traitement( n );

  printf("done...\n");
 
  return 0;
}
