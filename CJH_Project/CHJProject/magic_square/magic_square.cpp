#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int magicsquare[100][100];
void Drawmgs(int n)
{
	int count = 1;
	int row,colum;
	for(row = 0,colum=n/2;count<n*n+1;row--,colum++)
	{
		if(row < 0 && colum >= n)
		{
			row += 2;
			colum--;
			magicsquare[row][colum] = count;
			count++;
			continue;
		}
		else if (row<0)
		{
			row = n - 1;
			magicsquare[row][colum] = count;
			count++;
			continue;
		}
		else if (colum>=n)
		{
			colum = 0;
			magicsquare[row][colum] = count;
			count++;
			continue;
		}
		else if (magicsquare[row][colum]!=0)
		{
			row+=2;
			colum--;
			magicsquare[row][colum] = count;
			count++;
		}
		else
		{
			magicsquare[row][colum] = count;
			count++;
		}
		
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%4d ", magicsquare[i][j]);
		}
		printf("\n");
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	if (n%2!=0)
	{
		Drawmgs(n);
	}
}