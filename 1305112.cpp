#include<bits/stdc++.h>
using namespace std;
ifstream fin("in.txt");

int G[1000][1000];
int n;
int best=INT_MAX;
vector<int>finalPath;
void input()
{

    fin>>n;


    for(int i=0; i<(n*n-n)/2; i++)
    {
        int d,e,f;
        fin>>d>>e>>f;
        G[d][e]=f;
        G[e][d]=f;

    }

}

void tsp(int mask,int node,int cost, vector<int>cover)
{
    if(mask==(1<<n)-1)
    {
        int last=cost+G[0][node];

        if(last<best)
        {
            best=last;
            finalPath=cover;
        }
        return;
    }
    for(int i=0;i<n;i++)
    {
        int newmask=1<<i;
        //cout<<newmask<<" "<<mask<<endl;
        if((newmask & mask)==0)
        {
            vector<int>path=cover;
            path.push_back(i);
            tsp(mask|newmask,i,cost+G[node][i],path);
        }

    }
}

int main()
{
    input();
    vector<int>t;
    tsp(1,0,0,t);
    cout<<"Cost="<<best<<endl<<"Path: 0 ";
    for(vector<int>::iterator it=finalPath.begin();it!=finalPath.end();it++)cout<<*it<<" ";
    cout<<"0";

}
