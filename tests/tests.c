#include <stdio.h>
#include <unistd.h>

void main(int argv, char *argc[]) {
	int i = 1;
	while (i < argv) {
		switch (argc[i]) {
		case '1':
			if (test1() == 0) {
				fprintf(stdin, "%s : Test1 succed", argc[0]);
			}
			break;
		case '2':
			if (test2() == 0) {
				fprintf(stdin, "%s : Test2 succed", argc[0]);
			}
			break;
		case '3':
			if (test3() == 0) {
				fprintf(stdin, "%s : Test3 succed", argc[0]);
			}
			break;
		default:
			fprintf(stderr, "%s : Undefined Test %s", argc[0], argc[i]);
			break;
		}
	}
}
int test1() {
	/*ToDo*/
	return 0;
}
int test2() {
	/*ToDo*/
	return 0;
}
int test3() {
	/*ToDo*/
	return 0;
}