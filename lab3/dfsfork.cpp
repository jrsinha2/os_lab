#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
vector<int> g[N];
int vis[N];
#define pb push_back
void dfs(int k,int lvl)
{	if(vis[k])
		return;
	vis[k]=true;
	cout<<k<<" "<<lvl<<endl;
	for(int i=0;i<g[k].size();i++)
	{
		dfs(g[k][i],lvl+1);
	}

}
int main()
{	ifstream file("nodes");
	int v,u;
	int root = INT_MAX;
	file>>v;
	cout<<v<<endl;
	//cout<<par<<endl;
	while(file>>v>>u)
	{
		g[u].pb(v);
		root = min(root,min(u,v));
	}
	dfs(root,0);
	
}
