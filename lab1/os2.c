#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
int front,rear;

void bfs(char* path)
{	
	struct dirent* dir_ptr;
	DIR *dir = opendir(path);
	if(!dir)
	{			
		return;
	}
	
	char queue[1000][1000];				//queue to store path names
	int lvl[1000];							//to store level of nodes
	
	strcpy(queue[++rear],path);			//initial push to queue
	lvl[rear]=1;
	
	while(front !=rear)								//while queue is not empty
	{	char* path = queue[++front];		//extract current folder
		int level = lvl[front];
		
		DIR *dir = opendir(path);	//open current folder
		while(1)								//read all nodes i.e. all directories in a folder 
		{	
			dir_ptr = readdir(dir);
			if(dir_ptr==NULL)
			{	break;
			}
			if(strcmp(dir_ptr->d_name,".")!=0 && strcmp(dir_ptr->d_name,"..")!=0 )
			{	for(int i = 0 ; i< level ; i++)
					printf("-");
				printf("|");
				printf("%s\n",dir_ptr->d_name);
				
				char folder[1000];
				strcpy(folder, path);
				strcat(folder,dir_ptr->d_name);
				strcat(folder,"/");
				
				strcpy(queue[++rear],folder);				//push directory in queue and update its level
				lvl[rear] = level+1;
				
			}
		}
	}
	closedir(dir);
	 	
}
int main()
{	char path[1000];
	printf("enter the string \n");
	scanf("%s",path);
	
	front=-1,rear=-1;
	bfs(path);
	
	printf("\n");
	return 0;
}
