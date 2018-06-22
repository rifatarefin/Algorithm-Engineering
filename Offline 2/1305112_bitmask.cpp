#include<bits/stdc++.h>
using namespace std;
ifstream fin("in.txt");

int N,M;                         //N = number of subset;M = size of universe.
int a[1000];
double w[1000],minC=INT_MAX;
set<int>result;
void input()
{
    fin>>M>>N;
    string line;
    memset(a,0,sizeof(a));
    memset(w,0,sizeof(w));
    result.clear();
    minC=INT_MAX;

    for(int i=0;i<N;i++)
    {
        fin>>w[i];
        int c,num,mask=0;
        fin>>c;
        for(int j=0;j<c;j++)
        {
            fin>>num;
            mask|=1<<num;
        }

        a[i]=mask;
        //cout<<mask<<endl;              //print
    }

}

void subset(int mask, int idx, double cost, set<int>cover)
{
    if(idx==N && mask!=(1<<M)-1)return;
    else if(idx==N && mask==(1<<M)-1)
    {
        if(cost<minC)
        {
            minC=cost;
            result=cover;
        }
        return ;
    }
    set<int>nn=cover;
    nn.insert(idx);
    subset(mask|a[idx],idx+1,cost+w[idx],nn);
    subset(mask,idx+1,cost,cover);

}

int main()
{
    int tc;
    fin>>tc;
    for(int xx=0;xx<tc;xx++)
    {
        clock_t tStart = clock();
        input();
        set<int>sd;
        subset(0,0,0,sd);
        //cout<<"Cost="<<minC<<", Subsets: ";
        for(set<int>::iterator it=result.begin();it!=result.end();it++)cout<<*it<<", ";
        cout<<"Cost="<<minC<<" Time: "<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<"\n\n";

    }
}
