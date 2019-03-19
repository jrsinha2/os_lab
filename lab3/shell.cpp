//Program to create simple shell
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<sys/wait.h> 
#include<bits/stdc++.h>
using namespace std;

void listfiles(char* path,string parameter)
{	struct dirent* dir_ptr;
	DIR *dir  = opendir(path);
	if(!dir)
	{	return;
	}
	while(1)
	{	dir_ptr = readdir(dir);
		if(dir_ptr==NULL)
		{	return;
		}
		if(parameter=="")
		{	if(strcmp(dir_ptr->d_name,".")!=0 && strcmp(dir_ptr->d_name,"..")!=0)
			{	printf("%s\n",dir_ptr->d_name);
			}
		}	
		else if(parameter=="-a")
		{	printf("%s\n",dir_ptr->d_name);
		}
		else if(parameter=="-l")
		{	if(strcmp(dir_ptr->d_name,".")!=0 && strcmp(dir_ptr->d_name,"..")!=0)
			{	printf("%s\t",dir_ptr->d_name);
				struct stat fileStat;
				if(stat(dir_ptr->d_name,&fileStat)<0)
					cout<<"Cannot Access details\n";
				else
				{	
					//File Permissions
					printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
					printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
					printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
					printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
					printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
					printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
					printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
					printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
					printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
					printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
			
					//Number of Links
					cout<<"\t"<<fileStat.st_nlink;
			
					//File Size
					cout<<"\t"<<fileStat.st_size<<endl;
				}
			}
		}
		else if(parameter=="-al")
		{	printf("%s\t",dir_ptr->d_name);
			struct stat fileStat;
			if(stat(dir_ptr->d_name,&fileStat)<0)
				cout<<"Cannot Access details\n";
			else
			{	//File Permissions
				printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
				printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
				printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
				printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
				printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
				printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
				printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
				printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
				printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
				printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		
				//Number of Links
				cout<<"\t"<<fileStat.st_nlink;
		
				//File Size
				cout<<"\t"<<fileStat.st_size<<endl;
			}
		}
	}
}
int main()
{	char path[1000];
	cout<<"Enter the path of current directory for shell to work upon\n";
	scanf("%s",path);
	getchar();
	while(1)
	{	cout<<"~SinhaTerminal::";		//PathName
		cout<<path;
		
		
		string input;
		getline(cin,input);
		if(input == "exit" || input == "Exit")
			break;
		string Command="",Parameters[10];
		for(int i = 0;i<10;i++)
			Parameters[i]="";
		bool InputParameters=false;
		int i =0,cnt=0;
		while(i<input.size() && input[i]==' ')
			i++;
		while(i<input.size())
		{	if(input[i]!=' ')
			{	//cout<<input[i]<<" ";
				if(!InputParameters)
					Command+=(input[i]);
				else
					Parameters[cnt]+=(input[i]);
				
			}
			else
			{	if(!InputParameters)
				{	
					InputParameters=true;
				}
				else
				{	//cout<<"done\n";
					cnt++;
				}
				while(input[i]==' ')
					i++;
				i--;
			}
			i++;
		}
		if(input[input.size()-1]!=' ')
			cnt++;
		/*cout<<Command<<endl;
		for(int i =0;i<cnt;i++)
			cout<<Parameters[i]<<" ";
		cout<<"\n";
		*/
		
		if(Command=="ls")
		{	listfiles(path,Parameters[0]);
		}
		else if(Command=="cd")
		{	int len = strlen(path);
			if(Parameters[0]=="..")
			{	int len=strlen(path);
				int i =len-2;
				while(path[i]!='/')
				{	i--;
				}
				path[++i]='\0';
			}
			else if(Parameters[0]!="."){
			for(int i =0;i<Parameters[0].size();i++)
			{	path[len++]=Parameters[0][i];
			}
			path[len++]='/';
			path[len++]='\0';
			}
		}
		else if(Command == "rm")
		{	int len = strlen(path);
			char temppath[1000];
			strcpy(temppath,path);
			for(int i =0;i<Parameters[0].size();i++)
			{	temppath[len++]=Parameters[0][i];
			}
			temppath[len++]='/';
			temppath[len++]='\0';
			//cout<<temppath<<endl;
			//getchar();
			if(rmdir(temppath)==-1)
			{	cerr << "Error: " << strerror(errno) << endl;
			}
		}
		else if(Command == "mkdir")
		{	int len = strlen(path);
			char temppath[1000];
			strcpy(temppath,path);
			for(int i =0;i<Parameters[0].size();i++)
			{	temppath[len++]=Parameters[0][i];
			}
			temppath[len++]='/';
			temppath[len++]='\0';
			//cout<<temppath<<endl;
			//getchar();
			if(mkdir(temppath,0777)==-1)
			{	cerr << "Error: " << strerror(errno) << endl;
			}
		}
		else if(Command=="pwd")
		{
			cout<<path<<endl;
		}
		else
		{	cout<<Command<<" does not exist\n ";
		}
		
	}
	return 0;
}
