//page replacement fifo
#include<bits/stdc++.h>
using namespace std;
int main()
{	queue<int> q;
	map<int,int> mp;
	int size,cur=0;
	cout<<"Enter the capacity"<<endl;
	cin>>size;
	int pf=0,hits=0;	
	while(1)
	{	int ch;
		cin>>ch;
		if(ch==-1)
			break;
		if(mp.find(ch)==mp.end() || mp[ch]==0)
		{	cout<<"Page Fault\n";
			mp[ch]=1;
			pf++;
			if(cur==size){
			int removed = q.front();
			mp[removed]=0;
			q.pop();
			cur--;
			}
			q.push(ch);
			cur++;	
		}
		else
		{	cout<<"Hit"<<endl;
			hits++;
		}
		//cout<<cur<<endl;
		cout<<"Current Status\n";
		for(auto it :mp)
		{	if(it.second>0)
			cout<<it.first<<" ";
		}
		cout<<"\n";	

	}
	cout<<"Total no. of pagefaults  "<<pf<<endl;
	cout<<"Total no. of hits "<<hits<<endl;
	cout<<"Hit ratio "<<(double)hits/(double)(hits+pf)<<endl;
	return 0;
}
