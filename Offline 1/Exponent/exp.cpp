#include<bits/stdc++.h>
using namespace std;
ifstream fin("in.txt");


int G[1000][1000];
set<int>node;
int n;
int start=0;
vector<int>result;
int bestC=INT_MAX;

void input()
{

    fin>>n;
    for(int i=0;i<n;i++)
    {
        node.insert(i);
    }

    for(int i=0;i<(n*n-n)/2;i++)
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

    //vector<int>::iterator iit;
    if(cover.size()==n)
    {

        int c=cost+addcost(processing,start);
        que.push_back(start);
        if(c<bestC)
        {
            bestC=c;

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
    cout<<"\nPath\n";
    for(vector<int>::iterator it=result.begin();it!=result.end();it++)

        cout<<*it<<" ->";
    cout<<"Cost= "<<bestC;



}
