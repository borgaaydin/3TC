#include <stdio.h>
#define TAILLE 10

/*!
*********
* \brief remplit un tableau trie de 2N elements en fusionnant
* deux tableaux de N elements tries (N>1)
* \param T tableau de N entiers
* \param S tableau de N entiers
* \param TS tableau de 2N entiers resultat de la fusion
* \param N Taille des tableaux T et S
*********/
void 
fusion( int T[], 
	int S[], 
	int TS[], 
	int N)
{
	int s=0;
	int t=0;
	int fus=0;

	while((t<N) && (s<N))
	{
		if(T[t] < S[s])
		{
			TS[fus] = T[t];
			t++;
		}
		else
		{
			TS[fus] = S[s];
			s++;
		}
		fus++;
	}

	while(s<N)
	{
		TS[fus]=S[s];
		s++;
		fus++;
	}

	while(t<N)
	{
		TS[fus]=T[s];
		t++;
		fus++;
	}
}
