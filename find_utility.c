/*
 * This program provides an example of how to parse arguments using getopt().
 * This program can be integrated into your 2nd programming project about the
 * find utility to parse multiple arguments. Note that this example uses a
 * short option for command-line arguments, e.g. -n instead of -name, -m
 * instead of -mmin, and this is acceptable in your program too.
 * 
 * Compile this code: gcc -o getopt-example getopt-example.c
 * 
 * Sample run: 
 * $./getopt-example -w Document -n foo -a delete 
 * $./getopt-example -w Document -n myfile -a delete 
 * $./getopt-example -w Document -m -10
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define CURRENT_DIRECTORY "."
#define PARENT_DIRECTORY ".."
#define SLASH "/"

void read_sub(char *sub_dir)
{
	DIR *sub_dp = opendir(sub_dir);
	struct dirent *sub_dirp;
	if (sub_dp != NULL)
	{
		while ((sub_dirp = readdir(sub_dp)) != NULL)
		{
			//if(stat(sub_dirp->d_name,&buf)==0)
			//printf("%d ", (int)buf.st_size);
			char *cur_dir_name = sub_dirp->d_name;

			if (strcmp(cur_dir_name, CURRENT_DIRECTORY) != 0 && strcmp(cur_dir_name, PARENT_DIRECTORY) != 0) //recurcively loop into the sub-directory
			{
				printf("%s/%s\n", sub_dir, cur_dir_name);
				char temp3[] = "/";
                char *temp_sub = temp3;
                temp_sub = strcat(temp_sub, cur_dir_name);
                char *temp_full_path = malloc(sizeof(char) * 2000);
                temp_full_path = strcpy(temp_full_path, sub_dir);
                strcat(temp_full_path, temp_sub);
                DIR *subsubdp = opendir(temp_full_path);
                if (subsubdp != NULL)
                {
                    closedir(subsubdp);
                    read_sub(temp_full_path);
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

void find(char *where, char *name, char *action)
{
	/* Test arguments parsed. */
	printf("find %s %s %s\n", where, name, action);
	read_sub(where);
}

int main(int argc, char **argv)
{
	int w, n, m, i, a;
	char *where, *name, *mmin, *inum, *action;
	while (TRUE)
	{
		// TODO: Make it work when -w is not specified 
		char c;
		c = getopt(argc, argv, "w:n:m:i:a:");
		if (c == -1)
			break;
		switch (c)
		{
		case 'w':
			w = 1;
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
		case '?':
		default:
			printf("An invalid option detected.\n");
		}
	}

	if (a == 1 || w == 1 || n == 1)
		find(where, name, action);

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
