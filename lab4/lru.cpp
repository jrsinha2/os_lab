#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define S second
#define F first
int main()
{	queue<int> q;
	map<int,int> mp;
	int size ,cur = 0;
	static int t = 0;
	cout<<"Enter the capacity"<<endl;
	cin>>size;
	int pf = 0;
	int hit= 0;
	while(1)
	{	int ch;
		cin>>ch;
		if(ch==-1)
			break;
		if(mp.find(ch)==mp.end() || mp[ch]==0)
		{	cout<<"Page Fault\n";
			if(cur == size)
			{	int midx = 0;
				int mi = INT_MAX;
				for(auto it: mp)
				{	if(mi>it.S && it.S>0)
					{	midx = it.F;
						mi = it.S;
					}
				}
				mp[midx]=0;
				cur--;
				
			}
			mp[ch]=++t;
			pf++;
			cur++;
		}
		else
		{	mp[ch]=++t;
			cout<<"Hit\n";
			hit++;
		}
		cout<<"Current Status "<<endl;
		for(auto it : mp)
		{	if(it.S>0)
				cout<<it.F<<" ";
		}
		cout<<"\n";
	}
	cout<<"Total no. of page faults "<<pf<<endl;
	cout<<"Total no. of hits "<<hit<<endl;
	cout<<"hit ratio "<<(double)hit/(double)(hit+pf)<<endl;
	return 0;
}
