#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char key[255];
	char value[255];
} oh_option;

oh_option *oh_init(int argc, char *argv[]);

int oh_validate(oh_option *options, char *valid_options[], int number_options);

int oh_exists(oh_option *options, char option[]);
