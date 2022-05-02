#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>


#define TRUE 1
#define FALSE 0
#define CURRENT_DIRECTORY "."
#define PARENT_DIRECTORY ".."
#define SLASH "/"
#define SIZE 2000

// 1. find where-to-look
void find_functionality_1(char *where)
{

	DIR *sub_dp = opendir(where);
	struct dirent *sub_dirp;
	if (sub_dp != NULL)
	{
		while ((sub_dirp = readdir(sub_dp)) != NULL)
		{
			char *cur_dir_name = sub_dirp->d_name;

			//recurcively loop into the sub-directory
			if (strcmp(cur_dir_name, CURRENT_DIRECTORY) != 0 && strcmp(cur_dir_name, PARENT_DIRECTORY) != 0)
			{
				printf("%s/%s\n", where, cur_dir_name); // Print out the full path starting from the where location to the cur_dir_name
				
				char temp3[] = SLASH;
				char *temp_sub = (char *)malloc(SIZE *sizeof(char));
				strcpy(temp_sub, temp3);
				temp_sub = strcat(temp_sub, cur_dir_name);
				char *temp_full_path = malloc(sizeof(char) * SIZE);
				strcpy(temp_full_path, where);
				strcat(temp_full_path, temp_sub);
				DIR *subsubdp = opendir(temp_full_path);
				
				if (subsubdp != NULL)
				{
					closedir(subsubdp);
					find_functionality_1(temp_full_path);	// Recursive call with the new temp full path 
				}
			}
		}
		closedir(sub_dp);  // Close the directory 
	}
	else
	{
		printf("cannot open directory\n");
		exit(2);
	}
}

// 2.1 find where-to-look -name <specified name>
void find_functionality_2_1(char *where, char *name, int delete_flag)
{
	DIR *sub_dp = opendir(where);
	struct dirent *sub_dirp;
	if (sub_dp != NULL)
	{
		while ((sub_dirp = readdir(sub_dp)) != NULL)
		{
			char *cur_dir_name = sub_dirp->d_name;

			//recurcively loop into the sub-directory
			if (strcmp(cur_dir_name, CURRENT_DIRECTORY) != 0 && strcmp(cur_dir_name, PARENT_DIRECTORY) != 0)
			{
				char *dir_path = malloc(sizeof(char) * SIZE);
				strcpy(dir_path, where);
				strcat(dir_path, SLASH);
				strcat(dir_path, cur_dir_name);

				if (strcmp(cur_dir_name, name) == 0) //If the cur_dir_name is the same as the name specified then print
				{
					printf("%s\n", dir_path);
					if (delete_flag) remove(dir_path); // If the delete flag is turned on then remove it 
				}
				char temp3[] = SLASH;
				char *temp_sub = temp3;
				temp_sub = strcat(temp_sub, cur_dir_name);
				char *temp_full_path = malloc(sizeof(char) * SIZE);
				temp_full_path = strcpy(temp_full_path, where);
				strcat(temp_full_path, temp_sub);
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL)
				{
					closedir(subsubdp);
					find_functionality_2_1(temp_full_path, name, delete_flag); // recursively call with the new temp full path 
				}
			}
		}
		closedir(sub_dp);
	}
	else
	{
		printf("cannot open directory\n");
		exit(2);
	}
}

// 2.2 find where-to-look -mmin <specified number of minutes>
void find_functionality_2_2(char *where, int mmin, int op, int delete_flag)
{
	DIR *sub_dp = opendir(where);
	struct stat buf;
	struct dirent *sub_dirp;
	if (sub_dp != NULL)
	{
		while ((sub_dirp = readdir(sub_dp)) != NULL)
		{
			char *cur_dir_name = sub_dirp->d_name;
			//recurcively loop into the sub-directory
			if (strcmp(cur_dir_name, CURRENT_DIRECTORY) != 0 && strcmp(cur_dir_name, PARENT_DIRECTORY) != 0)
			{
				char *dir_path = malloc(sizeof(char) * SIZE);
				strcpy(dir_path, where);
				strcat(dir_path, SLASH);
				strcat(dir_path, cur_dir_name);

				if (stat(dir_path, &buf) == 0)	// If we are able to retrieve the stat of the current dir_path
				{
					long int t = (long int)(time(NULL) - buf.st_mtime);

					t = t / 60;
					// Switch based on the operation specified. 
					// If +10, then >10 
					// If -10, then <10 
					// If 10, then ==10
					switch (op)
					{
					case '>':
						if (t > mmin)
							printf("%s\n", dir_path);
							if (delete_flag) remove(dir_path); 
						break;
					case '<':
						if (t < mmin)
							printf("%s\n", dir_path);
							if (delete_flag) remove(dir_path); 
						break;
					default:
						if (t == mmin)
							printf("%s\n", dir_path);
							if (delete_flag) remove(dir_path); 
						break;
					}
				}
				char temp3[] = SLASH;
				char *temp_sub = temp3;
				temp_sub = strcat(temp_sub, cur_dir_name);
				char *temp_full_path = malloc(sizeof(char) * SIZE);
				temp_full_path = strcpy(temp_full_path, where);
				strcat(temp_full_path, temp_sub);
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL)
				{
					closedir(subsubdp);
					find_functionality_2_2(temp_full_path, mmin, op, delete_flag); // recursively traverse the directory 
				}
			}
		}
		closedir(sub_dp);
	}
	else
	{
		printf("cannot open directory\n");
		exit(2);
	}
}

// 2.3 find where-to-look -inum <specified i-node number>
void find_functionality_2_3(char *where, int inode, int delete_flag)
{
	DIR *sub_dp = opendir(where);
	struct dirent *sub_dirp;
	struct stat buf;
	if (sub_dp != NULL)
	{
		while ((sub_dirp = readdir(sub_dp)) != NULL)
		{
			char *cur_dir_name = sub_dirp->d_name;
			//recurcively loop into the sub-directory
			if (strcmp(cur_dir_name, CURRENT_DIRECTORY) != 0 && strcmp(cur_dir_name, PARENT_DIRECTORY) != 0)
			{
				char *dir_path = malloc(sizeof(char) * SIZE);
				strcpy(dir_path, where);
				strcat(dir_path, SLASH);
				strcat(dir_path, cur_dir_name);

				if (stat(dir_path, &buf) == 0) // Retrieve the stat for the cur dir_path 
				{
					int t = buf.st_ino;	
					if (t == inode)		// if the inode numbers are equal then print it, if delete flag is turned on then remove it 
					{
						printf("%s\n", dir_path);
						if (delete_flag) remove(dir_path); 
					}
				}

				char temp3[] = SLASH;
				char *temp_sub = temp3;
				temp_sub = strcat(temp_sub, cur_dir_name);
				char *temp_full_path = malloc(sizeof(char) * SIZE);
				temp_full_path = strcpy(temp_full_path, where);
				strcat(temp_full_path, temp_sub);
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL)
				{
					closedir(subsubdp);
					find_functionality_2_3(temp_full_path, inode, delete_flag);
				}
			}
		}
		closedir(sub_dp);
	}
	else
	{
		printf("cannot open directory\n");
		exit(2);
	}
}
int main(int argc, char **argv)
{
	// Argument defintions
	int w = 1;
	int n = 0;
	int m = 0;
	int i = 0;
	int a = 0;
	char *where, *name, *mmin, *inum, *action;
	where = NULL;
	while (TRUE)
	{
		char c;
		c = getopt(argc, argv, ":w:n:m:i:a:");
		if (c == -1)
			break;
		switch (c)
		{
		case 'w':
			where = optarg;
			printf("where: %s\n", optarg);
			break;
		case 'n':
			n = 1;
			name = optarg;
			printf("name: %s\n", optarg);
			break;
		case 'm':
			m = 1;
			mmin = optarg;
			printf("mmin: %s\n", optarg);
			break;
		case 'i':
			i = 1;
			inum = optarg;
			printf("inum: %s\n", optarg);
			break;
		case 'a':
			a = 1;
			action = optarg;
			printf("action: %s\n", optarg);
			break;
		case 1:
			printf("Non-optional arg: %s \n", optarg);
			break;
		case '?':
		default:
			printf("An invalid option detected.\n");
		}
	}

	if (w == 1)
	{	
		// If not where directory is speicified then use this 
		if (where==NULL) {
			where = ".";
		}
		// If directory is specified then use 1
		if (n == 0 && i == 0 && m == 0)
			find_functionality_1(where);
		// If name is specified then use 2.1 
		else if (n == 1)
			find_functionality_2_1(where, name, a); // a is the delete flag 
		// If mmin is specified then use 2.2 
		else if (m == 1)
		{
			char op;
			int mins = 0;
			if (mmin != NULL && mmin[0] != '\0')
			{
				char firstChar = mmin[0];
				switch (firstChar)
				{
				case '+':
					op = '>';
					break;
				case '-':
					op = '<';
					break;
				default:
					op = '=';
				}
				mins = abs(atoi(mmin));
			}
			find_functionality_2_2(where, mins, op, a); // a is the delete flag 
		}
		// If i-node is specified then use 2.3 
		else if (i == 1)
		{
			int inode = atoi(inum);
			find_functionality_2_3(where, inode, a); // a is the delete flag 
		}
	}

	argc -= optind;
	argv += optind;

	if (argc > 0)
	{
		printf("There are %d command-line arguments left to process:\n", argc);
		for (i = 0; i < argc; i++)
		{
			printf("Argument %d: '%s'\n", i + 1, argv[i]);
		}
	}
	return 0;
}
