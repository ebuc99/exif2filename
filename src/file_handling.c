#include <file_handling.h>
#include <time.h>
#ifdef _DIRENT_HAVE_D_TYPE
#define HAVE_D_TYPE 1
#else
#define HAVE_D_TYPE 0
#endif

int has_file_this_suffix(const char filename[], const char suffix[]) {
    int i;
	char temp_filename[strlen(filename)];
	char temp_suffix[strlen(filename)];
	for(i=0;filename[i] != '\0';++i)
		temp_filename[i] = tolower(filename[i]);
	int k = i-1;
	for(i=0;suffix[i] != '\0';++i)
		temp_suffix[i] = tolower(suffix[i]);
	int m;
	for(m=i-1;temp_filename[k] == temp_suffix[m] && k >= 0 && m >= 0; --k, --m);
	return ((m == -1) ? 1 : 0);
}

void get_current_time_str(char strtime[]) {
	time_t rawtime;
	time(&rawtime);
	strftime(strtime, 15, "%Y%m%d%H%M%S", localtime(&rawtime));
}

int get_number_files_in_dir() {
	struct dirent *ep;
	DIR *dp = opendir(".");
	uint16_t files = 0;
	if(dp == NULL) {
		perror("Kann Verzeichnis nicht öffnen!");
		return files;
	}
	while((ep = readdir(dp)) != NULL) {
		if(HAVE_D_TYPE) {
			if(ep->d_type == DT_REG)
				if(has_file_this_suffix(ep->d_name, "JPG"))
					++files;
		}
	}	
	closedir(dp);
	return files;
}

void get_files_from_dir(char *files[]) {
	struct dirent *ep;
	int i = 0;
	DIR *dp = opendir(".");
	if(dp == NULL) {
		perror("Kann Verzeichnis nicht öffnen!");
		return;
	}
	while((ep = readdir(dp)) != NULL) {
		if(HAVE_D_TYPE) {
			if(ep->d_type == DT_REG)
				if(has_file_this_suffix(ep->d_name, "JPG"))
					files[i++] = ep->d_name;
		}
	}
}

void write_backup_file(char* file_prefix, struct file_rename frename[], int cnt_files) {
	int i;
	FILE *backup_file;
	char file_line[100];
	char backup_filename[255];
	char strtime[15];
	get_current_time_str(strtime);
	strcpy(backup_filename, file_prefix);
	strcat(backup_filename, "backup_");
	strcat(backup_filename, strtime);
	strcat(backup_filename, ".sh");
	backup_file = fopen(backup_filename, "w+");
	for(i=0;i<cnt_files;++i) {
		sprintf(file_line, "mv %s %s\n", frename[i].new_name, frename[i].old_name);
		fputs(file_line, backup_file);
	}
	fclose(backup_file);
}

void rename_files(struct file_rename frename[], int cnt_files) {
	int i;
	int chk_rename = 0;
	for(i=0;i<cnt_files;++i)
		chk_rename = rename(frename[i].old_name, frename[i].new_name);
	if(chk_rename)
		printf("Error while renaming\n");
}
