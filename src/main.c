#include <file_handling.h>
#define MAXCHAR 20


void date2filename(const char str_prefix[], char str_in[], char str_out[]);

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Es muss ein Dateiprefix angegeben werden!\n");
		return EXIT_FAILURE;
	}
	char* file_prefix = argv[1];
	uint16_t cnt_files = get_number_files_in_dir();
	if(!cnt_files) {
		printf("Keine Dateien im Verzeichnis gefunden!\n");
		return EXIT_FAILURE;
	}
	char *files[cnt_files];
	struct file_rename frename[cnt_files];
	get_files_from_dir(files);
	int i;
	ExifData* data; 
	ExifEntry* entry; 
	char buf[1024];
	for(i = 0;i < cnt_files; ++i) {
		data = exif_data_new_from_file(files[i]);
		entry = exif_content_get_entry(data->ifd[0], EXIF_TAG_DATE_TIME); 
		if(entry) {
			exif_entry_get_value(entry, buf, sizeof(buf));
			date2filename(file_prefix, buf, frename[i].new_name);
			strcpy(frename[i].old_name, files[i]);
		}
	}
	write_backup_file(file_prefix, frename, cnt_files);
	rename_files(frename, cnt_files);
	return EXIT_SUCCESS;
}

void date2filename(const char str_prefix[], char str_in[], char str_out[]) {
	char str_temp[MAXCHAR+strlen(str_prefix)];
	strcpy(str_temp, str_prefix);
	char *token = strtok(str_in, ":");
	while(token != NULL) {
		strcat(str_temp, token);
		token = strtok(NULL, ":");
	}
	strcpy(str_out, "");
	token = strtok(str_temp, " ");
	while(token != NULL) {
		strcat(str_out, token);
		token = strtok(NULL, " ");
	}
	strcat(str_out, ".JPG");
}
