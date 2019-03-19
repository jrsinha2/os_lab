#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
void dfs(char* path,int lvl)
{	struct dirent* dir_ptr;				//declares a dirent type pointer

	DIR *dir = opendir(path);			//to get directory pointer by opendir
	if(!dir)
	{			
		return;
	}
	while(1)
	{	dir_ptr = readdir(dir);					// to get directory/files by readdir() function of dirent type
		if(dir_ptr==NULL)
		{	//printf("\n");
		
			break;
		}
		if(strcmp(dir_ptr->d_name,".")!=0 && strcmp(dir_ptr->d_name,"..")!=0 )				//so that not current folder or parent folder
		{	for(int i = 0 ; i< lvl ; i++)
				printf("-");
			printf("|");
			printf("%s\n",dir_ptr->d_name);			//d_name is variable in struct
			char folder[1000];
			strcpy(folder, path);				
			
			strcat(folder,dir_ptr->d_name);
			strcat(folder,"/");				//to make folder/
			//strcat(path,folder);
			//strcat(path,"/");
			//printf("%s\n",folder);
			
			dfs(folder,lvl + 1);			//depth first search call
		}
	}
	closedir(dir);
	 	
}
int main()
{	char path[1000];
	printf("enter the string \n");
	scanf("%s",path);
	
	dfs(path,1);
	
	printf("\n");
	return 0;
}
