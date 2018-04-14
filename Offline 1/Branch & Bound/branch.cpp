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

int checkBound(int a, int b, int cost, set<int>remain)
{
    int ed1=INT_MAX,ed2=INT_MAX;
    int total=cost;
    int newG[V][V];
    copy(&G[0][0], &G[0][0]+V*V,&newG[0][0]);
    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            if(remain.find(i)==remain.end() || remain.find(j)==remain.end())
            {
                newG[i][j]=0;
            }

            //cout<<newG[i][j]<<" ";
        }
        if(remain.find(i)!=remain.end())
        {
            if(G[a][i]<ed1)ed1=G[a][i];
            if(G[b][i]<ed2)ed2=G[b][i];
        }
    }
    total+=primMST(newG)+ed1+ed2;
    return total;

}

void exponent(set<int> cover,vector<int>que, int processing, int cost)
{


    vector<int>::iterator iit;
    if(cover.size()==v)
    {

        int c=cost+addcost(processing,start);
        if(c<bestC)
        {
            bestC=c;
            que.push_back(start);
            result=que;
        }

        for(vector<int>::iterator it=que.begin(); it!=que.end(); it++)

            cout<<*it<<" ->";
        cout<<"Cost= "<<c<<"\n";

        return;
    }
    set<int>remain;
    set_difference(node.begin(),node.end(),cover.begin(),cover.end(),inserter(remain,remain.end()));
    set<int>::iterator it;
    for(it=remain.begin(); it!=remain.end(); it++)
    {
        set<int>x=remain;
        x.erase(*it);
        int r=checkBound(start,*it,cost+addcost(processing, *it), x);
        cout<<r<<"\n";
        if(r>bestC)
        { cout<<"cut\n";
            return;
        }
        set<int>nn=cover;
        nn.insert(*it);
        vector<int>q=que;
        q.push_back(*it);
        exponent(nn, q, *it, cost+addcost(processing, *it));
    }


}
int main()
{

    input();

    set<int>st;
    vector<int>q;
    q.push_back(start);
    st.insert(start);
//    cout<<primMST(G);
//    checkBound(0,2,20,st);
//    st.insert(1);
//    checkBound(0,2,20,st);

    exponent(st, q, start, 0);

    for(vector<int>::iterator it=result.begin(); it!=result.end(); it++)

        cout<<*it<<" ->";
    cout<<"Cost= "<<bestC;




}
