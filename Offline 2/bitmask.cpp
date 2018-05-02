#include<bits/stdc++.h>
using namespace std;
ifstream fin("in.txt");

int N,M;                         //N = number of subset;M = size of universe.
int a[1000];
double w[1000];
set<int>result;
void input()
{
    fin>>M>>N;
    string line;
    memset(a,0,sizeof(a[0]));
    memset(w,0,sizeof(w[0]));
    result.clear();
    getline(fin,line);
    for(int i=0;i<N;i++)
    {
        getline(fin,line,' ');
        //cout<<line<<endl;           //print
        w[i]=stod(line);
        getline(fin,line);
        istringstream is(line);
        int num,mask=0;
        while(is>>num)
        {
            mask|=1<<num;
        }
        a[i]=mask;
        //cout<<mask<<endl;              //print
    }


}

double subset(int mask, int idx)
{
    if(idx==N && mask!=(1<<M)-1)return 99999;
    else if(idx==N && mask==(1<<M)-1)return 0;
    double take=subset(mask|a[idx],idx+1)+w[idx];
    double discard=subset(mask,idx+1);
    //cout<<w[idx]<<endl;;
    double t= min(take,discard);
    if(t==take)result.insert(idx);
    return t;
}

int main()
{
    int tc;
    fin>>tc;
    for(int xx=0;xx<tc;xx++)
    {
        input();
        double setsum= subset(0,0);
        cout<<setsum<<endl;
        for(set<int>::iterator it=result.begin();it!=result.end();it++)cout<<*it<<" ";
        cout<<"\n";

    }
}
