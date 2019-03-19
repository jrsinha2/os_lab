#include<bits/stdc++.h>
using namespace std;
int main()
{
	int frames;
	cout<<"Enter the number of frames\n";
	cin>>frames;
	int size;
	cout<<"Enter the size of the reference string\n";	
	cin>>size;
	int referencestring[size];
	map<int,int> future,present,temp;
	for(int i =0;i<size;i++)
	{	cin>>referencestring[i];
		future[referencestring[i]]++;
	}
	int filledframes = 0;
	int pagefaults=0,hits=0;
	map<int,bool> inMemory;

	for(int i =0;i<size;i++)
	{	temp = future;
		cout<<"current page: "<<referencestring[i]<<" ";
		if(inMemory[referencestring[i]]==false)
		{	cout<<"Page Fault ";
			if(filledframes<frames)
			{	cout<<"Not present\n";
				filledframes++;
				future[referencestring[i]]--;
				present[referencestring[i]]++;
				inMemory[referencestring[i]] = true;
				pagefaults++;
			}
			else
			{	//Finding the page that does not come in future
				int needToBeReplaced = -1;
				bool found = false;
				for(auto it : future)
				{
					if(it.second == 0 && inMemory[it.first] == true)
					{	needToBeReplaced = it.first;
						found = true;
						break;
					}
					if(found)
						break;
				}
				if(!found)
				{	//Finding that comes farthest in future
					for(int j = size - 1;j>i;j--)
					{	if(temp[referencestring[j]]==1 && inMemory[referencestring[j]] == true)
						{	found = true;
							needToBeReplaced = referencestring[j];
							
							break;
						}
						else
						{
							temp[referencestring[j]]--;
						}

					}
				}
				cout<<"need to be replaced "<<needToBeReplaced<<endl;
				inMemory[needToBeReplaced]=false;
				inMemory[referencestring[i]]=true;
				future[referencestring[i]]--;
				present[referencestring[i]]++;
				pagefaults++;

			}	

			
		}
		else
		{	cout<<"Hit\n";
			future[referencestring[i]]--;
			present[referencestring[i]]++;
			hits++;
		}
		cout<<"Current Status: ";
		for(auto it : inMemory)
		{
			if(it.second == true)
				cout<<it.first<<" ";
		}
		cout<<"\n\n";
	}
	cout<<"No. of Page Faults "<<pagefaults<<endl;
	cout<<"No. of Hits "<<hits<<endl;
	cout<<"Hit Ratio "<<(double)hits/(double)(pagefaults+hits)<<endl;
	return 0;
}