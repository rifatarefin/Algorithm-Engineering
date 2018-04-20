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
int newG[V][V];
int checkBound(int a, int b, int cost, set<int>remain)
{
    //if(remain.size()==0)return 0;
    int ed1=INT_MAX,ed2=INT_MAX;
    int total=cost;
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            newG[i][j]=G[i][j];
            //cout<<G[i][j]<<" ";
        }//cout<<endl;
    }

    //copy(&G[0][0], &G[0][0]+v*v,&newG[0][0]);


    for(int i=0; i<v; i++)
    {
        for(int j=0; j<v; j++)
        {
            if(remain.find(i)==remain.end() || remain.find(j)==remain.end())
            {
                newG[i][j]=0;
                newG[j][i]=0;
            }

            //cout<<newG[i][j]<<" ";
        }
        if(remain.find(i)!=remain.end())
        {
            if(G[a][i]<ed1)ed1=G[a][i];
            if(G[b][i]<ed2)ed2=G[b][i];
        }
    }


    int pri=0;
    if(remain.size()>1)pri=primMST(newG,*(remain.begin()));

    total+=pri+ed1+ed2;
    return total;

}

void exponent(set<int> cover,vector<int>que, int processing, int cost)
{

    set<int>remain;
    set_difference(node.begin(),node.end(),cover.begin(),cover.end(),inserter(remain,remain.end()));
    if(remain.size()==1)
    {
        int last=*(remain.begin());
        int c=cost+addcost(processing,last)+addcost(last,start);
        que.push_back(last);
        que.push_back(start);
        if(c<bestC)
        {
            bestC=c;

            result=que;
        }

//        for(vector<int>::iterator it=que.begin(); it!=que.end(); it++)    //print
//
//            cout<<*it<<" ->";
//        cout<<"Cost= "<<c<<"\n";

        return;
    }

    set<int>::iterator it;
    for(it=remain.begin(); it!=remain.end(); it++)
    {
        set<int>x=remain;
        x.erase(*it);

        int r=checkBound(start,*it,cost+addcost(processing, *it), x);
        //cout<<r<<endl;
        if(r>bestC)
        {
            //cout<<"cut\n";
            continue;
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

    int tc;
    fin>>tc;
    for(int zx=0; zx<tc; zx++)
    {
        clock_t tStart = clock();
        result.clear();
        node.clear();
        bestC=INT_MAX;
        input();



        set<int>st;
        vector<int>q;
        q.push_back(start);
        st.insert(start);


        exponent(st, q, start, 0);

        cout<<"PATH\n";
        for(vector<int>::iterator it=result.begin(); it!=result.end(); it++)

            cout<<*it<<" ->";
        cout<<"Cost= "<<bestC<<" Time: "<<(double)(clock() - tStart)/CLOCKS_PER_SEC<<endl;
    }




}
//for(int i=0;i<v;i++)
//    {
//        for(int j=0;j<v;j++)
//        {
//            cout<<G[i][j]<<" ";
//        }cout<<endl;
//    }




//for(set<int>::iterator it=remain.begin();it!=remain.end();it++)               //print
//    {
//        cout<<*it<<" ";
//    }cout<<"\n";
