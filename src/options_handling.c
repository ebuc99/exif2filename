#include "options_handling.h"
int get_number_of_options(int argc, char *argv[]) {
	int i;
	int number = 0;
	for(i = 1; i < argc; i++) {
		if(*argv[i] == '-')
			number++;
	}
	return number;
}

oh_option *oh_init(int argc, char *argv[]) {
	oh_option *options = malloc((sizeof(oh_option) * get_number_of_options(argc, argv)) + 1);
	int i;
	int j = 0;
	char *pos;
	for(i = 1; i < argc; i++) {
		if(*argv[i] == '-') {
			pos = strchr(argv[i], '=');
			if(pos){
				*pos = '\0';
				strncpy((options+j)->value, pos + 1, 255);
				pos = 0;
			}
			strncpy((options+j++)->key, argv[i], 255);
		}
	}
	strncpy((options+j)->key, "", 0); //Endekennung
	return options;
}

int oh_validate(oh_option *options, char *valid_options[], int number_options) {
	int i,j;
	int valid;
	for(i = 0; strcmp((options+i)->key, ""); i++) {
		valid = 0;
		for(j = 0; j < number_options; j++) {
			if(!strcmp((options+i)->key, valid_options[j])) {
				valid = 1;
				break;
			}
		}
		if(!valid) {
			printf("%s not a valid option, see --help\n", (options+i)->key);
			return valid;
		}
	}
	return 1;
}

int oh_exists(oh_option *options, char option[]) {
	int i;
	for(i = 0; strcmp((options+i)->key, ""); i++) {
		if(!strcmp((options+i)->key, option))
			return 1;
	}
	return 0;
}
