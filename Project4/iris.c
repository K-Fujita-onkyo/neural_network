/*************************************************************/
/* C-program for self-organized learning of Kohonen network  */
/*                                                           */
/* The purpose here is to find the representatives of p      */
/* clusters in the pattern space. If you can provide the     */
/* the training samples x, and speicify the number p, you    */
/* can use this program easily                               */
/*                                                           */
/*  1) Number of input : I                                   */
/*  2) Number of neurons: M                                  */
/*  3) Number of training patterns: P                        */
/*                                                           */
/* This program is produced by Qiangfu Zhao.                 */
/* You are free to use it for educational purpose            */
/*************************************************************/

/*
Kazuki Fujita: m5261108
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define I 4
#define M 3
#define P 150
#define alpha 0.5
#define n_update 20

double w[M][I];
double x[P][I];
double y[M];

/*************************************************************/
/* Print out the result of the q-th iteration                */
/*************************************************************/
void PrintResult(int q)
{
	int m, i;

	printf("\n\n");
	printf("Results in the %d-th iteration: \n", q);
	for (m = 0; m < M; m++)
	{
		for (i = 0; i < I; i++)
			printf("%5f ", w[m][i]);
		printf("\n");
	}
	printf("\n\n");
}

/*************************************************************/
/* The main program                                          */
/*************************************************************/
int main()
{
	int m, m0, i, j, p, q;
	double norm, s, s0;

	/* Initialization of the connection weights */

	for(i=0;i<P;i++){
		for(j=0;j<I;j++){
			scanf("%lf",&x[i][j]);
		}
	}

	for (m = 0; m < M; m++)
	{
		norm = 0;
		for (i = 0; i < I; i++)
		{
			w[m][i] = (double)(rand() % 10001) / 10000.0 - 0.5;
			norm += w[m][i] * w[m][i];
		}
		norm = sqrt(norm);
		for (i = 0; i < I; i++)
			w[m][i] /= norm;
	}

	PrintResult(0);

	/* Unsupervised learning */

	for (q = 0; q < n_update; q++){
		for (p = 0; p < P; p++){
			s0 = 0;
			for (m = 0; m < M; m++){
				s = 0;
				for (i = 0; i < I; i++) s += fabs(x[p][i]-w[m][i]);
				if (s > s0){
					s0 = s;
					m0 = m;
				}
			}
			//Update the weight of the winner

			printf("winner:%d\n",m0);
			for (i = 0; i < I; i++) w[m0][i] += alpha * (x[p][i] - w[m0][i]);

			norm = 0;

			for (i = 0; i < I; i++) norm += w[m0][i] * w[m0][i];

			norm = sqrt(norm);

			for (i = 0; i < I; i++)w[m0][i] /= norm;
		}
		PrintResult(q);
	}

	/* Classify the training patterns */

	for (p = 0; p < P; p++){
		s0 = 0;
		for (m = 0; m < M; m++){
			s = 0;
			for (i = 0; i < I; i++) s += w[m][i] * x[p][i];
			//printf("m=%d, s=%lf, s0=%lf\n", m, s, s0);
			if (s >= s0){
				s0 = s;
				m0 = m;
			}
		}
		printf("Pattern[%d] belongs to %d-th class\n", p, m0);
	}
}