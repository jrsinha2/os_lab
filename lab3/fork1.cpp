#include<bits/stdc++.h>
#include <sys/types.h>
#include<unistd.h>
using namespace std;
const int N = 1e5+5;
vector<int> g[N];
int vis[N];
#define pb push_back
int main()
{	int pid0,pid1,pid2,pid3;
	cout<<getpid()<<endl;
	pid0 = fork();
	if(pid0 == 0)
	{	
		int par = getppid();
		int child = getpid();
		sleep(3); 
		cout<<child<<" "<<par<<endl;
		g[par].pb(child);	
			
	}
	else
	{	sleep(3);
		//cout<<"parent process "<<getpid()<<endl;
	}
	pid1 = fork();
	if(pid1 == 0)
	{	int par = getppid();
		int child = getpid();
		sleep(3);
		cout<<child<<" "<<par<<endl;
		g[par].pb(child);	
			
	}
	else
	{	sleep(3);
		//cout<<"parent process "<<getpid()<<endl;
	}
	pid2 = fork();
	if(pid2 == 0)
	{	int par = getppid();
		int child = getpid();
		sleep(3);
		cout<<child<<" "<<par<<endl;
		g[par].pb(child);	
	}
	else
	{	sleep(3);
		//cout<<"parent process "<<getpid()<<endl;
	}
	
	return 0;
}
