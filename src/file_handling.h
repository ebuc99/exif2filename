#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <libexif/exif-data.h>

struct file_rename {
	char old_name[255];
	char new_name[255];
};

// get number of files in directory
int get_number_files_in_dir();

// get files from dir with suffix jpg
void get_files_from_dir(char *files[]);

// write backup file
void write_backup_file(char* file_prefix, struct file_rename frename[], int cnt_files); 

// rename files
void rename_files(struct file_rename frename[], int cnt_files);
