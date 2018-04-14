#include<bits/stdc++.h>
using namespace std;
#include "prim.cpp"
ifstream fin("in.txt");


int G[1000][1000];
set<int>node;
int v; //extern
int start=0;
vector<int>result;
int bestC=INT_MAX;

void input()
{

    fin>>v;
    for(int i=0;i<v;i++)
    {
        node.insert(i);
    }

    for(int i=0;i<(v*v-v)/2;i++)
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
        return;
    }
    set<int>remain;
    set_difference(node.begin(),node.end(),cover.begin(),cover.end(),inserter(remain,remain.end()));
    set<int>::iterator it;
    for(it=remain.begin();it!=remain.end();it++)
    {
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
    exponent(st, q, start, 0);

    for(vector<int>::iterator it=result.begin();it!=result.end();it++)

        cout<<*it<<" ->";
    cout<<"Cost= "<<bestC;
    primMST(G);



}
