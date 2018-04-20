
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
ofstream fout("out.txt");

int main() {
	// your code goes here
	int tc=20;
	for(int i=3; i<=11;i++)
	{
		fout<<i<<"\n";
		for(int j=0;j<i;j++)
		{
			for(int k=j+1;k<i;k++)
			{
				int c=rand()%(INT_MAX/6);
				c*=5;
				c=5+(c%50);
				fout<<j<<" "<<k<<" "<<c<<"\n";
			}

		}
	}
	return 0;
}
