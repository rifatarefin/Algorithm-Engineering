#include<bits/stdc++.h>
using namespace std;
#include "prim.cpp"
ifstream fin("in.txt");

#define V 1000
int G[V][V];
set<int>node;
int v; //extern
int start=0;
vector<int>result;
int bestC=INT_MAX;

map<int, vector<int> >childs;

void input()
{

    fin>>v;
    for(int i=0; i<v; i++)
    {
        node.insert(i);
    }

    for(int i=0; i<(v*v-v)/2; i++)
    {
        int d,e,f;
        fin>>d>>e>>f;
        G[d][e]=f;
        G[e][d]=f;

    }

}
int addcost(int a, int b)
{
    return G[a][b];
}

void trav(int s, int cost)
{
    cout<<s<<" ->";
    result.push_back(s);
    map<int, vector<int> >::iterator it;
    it=childs.find(s);
    if(it==childs.end())
    {
        return;
    }
    vector<int> vb=it->second;
    for(vector<int>::iterator j=vb.begin(); j!=vb.end(); j++)
    {
        trav(*j,cost+addcost(s,*j));
    }


}

int main()
{
    int tc;
    fin>>tc;
    for(int zx=0; zx<tc; zx++)

    {
        clock_t tStart = clock();
        node.clear();
        result.clear();
        bestC=INT_MAX;
        childs.clear();
        input();
        int *parent=primMST(G);

        for(int i=0; i<v; i++)
        {
            for(int j=0; j<v; j++)
            {
                if(parent[j]==i)
                {
                    childs[i].push_back(j);
                }
            }
        }cout<<"Path"<<endl;
        trav(0,0);

        int cost=0;
        for(int i=1; i<v; i++)
        {
            cost+=G[result[i-1]][result[i]];
        }
        cost+=G[result[v-1]][0];
        cout<<"0->Cost="<<cost<<" Time: "<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
    }







}
