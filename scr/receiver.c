#include <stdio.h>
#include <unistd.h>

void main(int argv, char *argc[]) {
	int opt , fileSelect = 0;
	char * filename;
	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {
		case 'f':
			if (fileSelect == 1) {
				fprintf(stderr, "%s: File have already been defined", argv[0]);
				exit(EXIT_FAILURE);}
			/*filename from (optarg)*/
			fileSelect = 1;
			break;
		default:
			fprintf(stderr, "%s: Un recognized\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (argv < (optind + 1)) {
		fprintf(stderr, "%s: Missing argument", argv[0]);
		exit(EXIT_FAILURE);}
	if (argv > (optind + 1)) {
		fprintf(stderr, "%s: Too many argument", argv[0]);
		exit(EXIT_FAILURE);}

	char * hostname = argc[optind];
	char * port = argc[optind + 1];

	/*suite*/
}
