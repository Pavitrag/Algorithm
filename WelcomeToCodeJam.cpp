#if BACKTRACK_SOL
#include<iostream>
#include<cstring>

using namespace std;

#define W_CHAR 0
#define E_CHAR 1
#define L_CHAR 2
#define C_CHAR 3
#define O_CHAR 4
#define M_CHAR 5
#define SPACE_CHAR 6
#define T_CHAR 7
#define D_CHAR 8
#define J_CHAR 9
#define A_CHAR 10

#define DISTINCT_CHARS 11
#define MAXCANDIDATES 500

int ln[DISTINCT_CHARS];

int is_a_solution(int out[], int outLen, int k)
{
  return (outLen == k);
}
const int welcomeTocodejam[] = 
{
		W_CHAR, 
		E_CHAR, 
		L_CHAR, 
		C_CHAR, 
		O_CHAR,
		M_CHAR, 
		E_CHAR, 
		SPACE_CHAR, 
		T_CHAR, 
		O_CHAR, 
		SPACE_CHAR, 
		C_CHAR, 
		O_CHAR, 
		D_CHAR, 
		E_CHAR,
		SPACE_CHAR, 
		J_CHAR, 
		A_CHAR, 
		M_CHAR
};
void construct_candidates(unsigned int **a, int k, int c[],
		int *ncandidates, int output[], int outLen)
{
	*ncandidates = 0;
	if (k == 0)
	{
		*ncandidates = ln[welcomeTocodejam[k]];
		for (int i = 0; i < ln[welcomeTocodejam[k]]; i++)
			c[i] = a[welcomeTocodejam[k]][i];
	} else // if(k > 0)
	{
		for (int i = 0; i < ln[welcomeTocodejam[k]]; i++)
			if (a[welcomeTocodejam[k]][i] > output[k - 1])
			{
				c[*ncandidates] = a[welcomeTocodejam[k]][i];
				(*ncandidates)++;
			}
	}
	return;
}

/*
 Params:
 a = holds indices of the "welcome to code jam chars",
 k = current character in the reckoning
 input = chars for which permissible indices has been considered

 */

#define MAXCANDIDATES 500
#define WTCJ 19 //length of "WELCOME TO CODE JAM"
#define FALSE 0

int backtrack(unsigned int** a, int k, int output[], int outlen)
{
	int count = 0;
	int c[MAXCANDIDATES]; /* candidates for next position */
	int ncandidates; /* next position candidate count */
	int i; /* counter */

	if (is_a_solution(output, outlen, k+1))
		return 1; //process_solution(a,k,input);
	else
	{
		k = k + 1;
		construct_candidates(a, k, c, &ncandidates, output, outlen);
		for (i = 0; i < ncandidates; i++)
		{
			output[k] = c[i];
			count += backtrack(a, k, output, outlen);
		}
	}
	return count;
}

unsigned int **fillIndex(string str)
{
	unsigned int **occurs = new unsigned int*[DISTINCT_CHARS];
	for (int i = 0; i < DISTINCT_CHARS; i++)
	{
		occurs[i] = new unsigned int[MAXCANDIDATES];
		memset(occurs[i], 0, sizeof(unsigned int) * MAXCANDIDATES);
	}

	for (int i = 0; i < (int)str.length(); i++)
	{
		switch (str[i])
		{
		case 'w':
			occurs[W_CHAR][ln[W_CHAR]++] = i;
			break;
		case 'e':
			occurs[E_CHAR][ln[E_CHAR]++] = i;
			break;
		case 'l':
			occurs[L_CHAR][ln[L_CHAR]++] = i;
			break;
		case 'c':
			occurs[C_CHAR][ln[C_CHAR]++] = i;
			break;
		case 'o':
			occurs[O_CHAR][ln[O_CHAR]++] = i;
			break;
		case 'm':
			occurs[M_CHAR][ln[M_CHAR]++] = i;
			break;
		case ' ':
			occurs[SPACE_CHAR][ln[SPACE_CHAR]++] = i;
			break;
		case 't':
			occurs[T_CHAR][ln[T_CHAR]++] = i;
			break;
		case 'd':
			occurs[D_CHAR][ln[D_CHAR]++] = i;
			break;
		case 'j':
			occurs[J_CHAR][ln[J_CHAR]++] = i;
			break;
		case 'a':
			occurs[A_CHAR][ln[A_CHAR]++] = i;
			break;
		}
	}
	return occurs;
}

void welcomeCodeJamDriver()
{
	string str("wweellccoommee to code qps jam");
	int output[WTCJ] = { 0, };
	unsigned int **a = fillIndex(str);
	cout << "output = " << backtrack(a, -1, output, WTCJ) << endl;

}

#else
/////////////DYNAMIC PROGRAMMING SOLUTION//////////////

#include<iostream>
#include<string>
#include<istream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include<cstdlib>

#define MAXCANDIDATES 505
#define WTCJ 19 //length of "WELCOME TO CODE JAM"
#define C_MODULO 10000

using namespace std;

int welcomeToCodeJamDP(char *str, int len, char *wel, int size)
{
   unsigned int **dp = new unsigned int*[len];
   for (int i = 0; i < len; i++)
   {
       dp[i] = new unsigned int[size];
       memset(dp[i], 0, sizeof(unsigned int) * size);
   }

   for(int i = 0; i<len; i++)
       if(str[i] == wel[0])
           dp[i][0] = ((i == 0)? 1 : 1 + dp[i-1][0]);
       else
           dp[i][0] = ((i == 0)? 0 : dp[i-1][0]);

   for(int i = 1; i<len; i++)
       for(int j = 1; j<size; j++)
       {
           dp[i][j] = dp[i-1][j];
           if(str[i] == wel[j])
               dp[i][j] = ((dp[i][j] + dp[i-1][j-1])%C_MODULO);
       }

   unsigned int retVal = dp[len-1][size-1];
   //free dp memory
   for (int i = 0; i < len; i++)
       delete []dp[i];
   delete dp;
   /////////////////
   return retVal;
}

void  welcomeCodeJamDriver()
{
   char *file = "<<SOME ABSOLUTE FILE PATH>>";
   FILE *fp = fopen(file, "r");
   if(!fp)
   {
       cout << "input file does not exist..Aborting" << endl;
       return;
   }
   int tcases=0;
   //fscanf(fp, "%d", &tcases);
   //ifs >> tcases;
   char s[MAXCANDIDATES];
   fgets(s, MAXCANDIDATES, fp);
   tcases = atoi(s);
   //string s;
   for(int i = 0; i < tcases; i++)
   {
       //getline(ifs, s);
       fgets(s, MAXCANDIDATES, fp);
       printf("Case #%d: %04d\n", i+1, welcomeToCodeJamDP(s, strlen(s), "welcome to code jam", WTCJ));
   }
   fclose(fp);
   return;
}

#endif
