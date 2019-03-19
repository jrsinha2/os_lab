#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<bits/stdc++.h>
using namespace std;
char ans[1000];
map<char,int> mp;
void trim(char* str)
{	
	int i=0,k=0;
	while(str[i]==' ')
		i++;
	//ans[k++]=(char)tolower(str[i++]);
	bool cap = false;
	while(i<strlen(str))
	{	if(str[i]==' ')
		{	while(str[i]==' ')
			{	i++;
			}
			ans[k++]=' ';
			//if(i<strlen(str)-1)
				//ans[k++]=(char)toupper(str[i++]);
		}
		else
		{	if(mp[str[i]]==1)
			{	ans[k++]=str[i++];
				ans[k++]=' ';
				cap = true;
			}
			else
			{	if(!cap)
					ans[k++]=(char)tolower(str[i++]);
				else
				{	//ans[k++]=(char)toupper(str[i++]);
					cap = false;
				}
			}
		}
	}
	ans[k]='\0';
	strcpy(str,ans);
	//cout<<ans<<endl;
	
}
void capitalize(char* str)
{	int i=0,k=0;
	bool cap = true;
	
	while(i<strlen(str))
	{	if(str[i]==' ')
			cap=true;
		else
		{	if(cap)
			{	str[i]=(char)toupper(str[i]);
				cap =false;
			}
			else
			{		str[i]=(char)tolower(str[i]);
			}
				
		}
		i++;
	
	}
}

int count(char* str)
{	int n =strlen(str);
	int c = 0;
	for(int i=0;i<n;i++)
	{	if(str[i]==' ' )
			c++;
	}
	c++;
	return c;
}
int main() 
{	mp[',']=1;
	mp['.']=1; 
	int fd1[2];  // Used to store two ends of first pipe 
  int fd2[2];  // Used to store two ends of second pipe 
  int fd3[2];
  char input_str[1000]; 
  pid_t p,q; 
  if (pipe(fd1)==-1) 
  { 
      fprintf(stderr, "Pipe Failed" ); 
      return 1; 
  } 
  if (pipe(fd2)==-1) 
  { 
      fprintf(stderr, "Pipe Failed" ); 
      return 1; 
  }
  if (pipe(fd3)==-1) 
  { 
      fprintf(stderr, "Pipe Failed" ); 
      return 1; 
  } 
	ifstream file("input");
	string line;
	getline(file,line);
	int j=0;
	for(int i=0;i<line.size();i++)
	{	input_str[j++]=line[i];
	}
	input_str[j]='\0';
  int par = getpid();
  //cout<<par<<endl;
  p = fork(); 
  //sleep(3);
	if (p < 0) 
  { fprintf(stderr, "fork Failed" ); 
    return 1; 
  } 
	else if (p > 0) 
  { //par = getpid();
  	
		close(fd1[0]);  // Close reading end of first pipe 
		
		write(fd1[1], input_str, strlen(input_str)+1); 
    cout<<"first process send string to second\n";
    close(fd1[1]); 
		sleep(5);	
		
		
		close(fd3[1]); // Close writing end of second pipe 
		char temp_str[100];
		strcpy(temp_str,""); 
		read(fd3[0], temp_str, 100); 
		//cout<<temp_str;
    printf("No. of characters %s\n",temp_str); 
    close(fd3[0]);
    
		 
  } 

  // child process 
  else
	{ q = fork();
		//sleep(3);
		if(q<0)
		{	cout<<"fork failed\n";
			return 1;
		}
		else if(q>0){
			//sleep(3);
			close(fd1[1]);
			char temp_str[1000]; 
			
			read(fd1[0], temp_str, 1000); 
			cout<<"second process receives it from first\n";
			close(fd1[0]); 
			
			close(fd2[0]); 
			trim(temp_str);
			cout<<"Trimmed String is "<<temp_str<<endl;
			write(fd2[1], ans, strlen(temp_str)+1); 
			cout<<"second process sends it to third process\n";
			close(fd2[1]);
		
			
		}
		else if (q==0)
		{	sleep(1);
			close(fd2[1]);  // Close writing end of first pipe 
			char temp_str[1000]; 
			 
			read(fd2[0], temp_str, 1000); 
			close(fd2[0]); 
			cout<<"third process receives it\n";
			capitalize(temp_str);
			cout<<"Capitalized string is "<<temp_str<<endl;
			cout<<"third process sends it to first process\n";
			close(fd3[0]); 
			int cnt = count(temp_str);
			//cout<<cnt<<endl;
			char snt[1000];
			string snt1 = to_string(cnt);
			int l1 = 0;
			for(int i=0;i<snt1.size();i++)
				snt[l1++]=snt1[i];
			snt[l1]='\0';
			//cout<<snt;
			
			close(fd3[0]); 
			write(fd3[1], snt, strlen(snt) +1); 
			close(fd3[1]);
			//sleep(2);
		}
		
		
  }
 
  //cout<<'\n';
  return 0; 
} 
