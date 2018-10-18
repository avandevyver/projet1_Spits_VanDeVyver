#include "packet.h"

#include <stdio.h>
#include <unistd.h>

void main(int argv, char *argc[]) {
	int i = 1;
	while (i < argv) {
		switch (argc[i]) {
		case '1':
			if (test1() == 0) {
				fprintf(stdin, "%s : Test1 succed\n", argc[0]);
			}
			break;
		case '2':
			if (test2() == 0) {
				fprintf(stdin, "%s : Test2 succed\n", argc[0]);
			}
			break;
		case '3':
			if (test3() == 0) {
				fprintf(stdin, "%s : Test3 succed\n", argc[0]);
			}
			break;
		default:
			fprintf(stdin, "%s : Undefined Test %s\n", argc[0], argc[i]);
			break;
		}
	}
}
int test1() {
	struct pkt_t* pkt = pkt_new();
	int dia = 0;
	if (pkt == NULL) {
		printf("Test1 : pkt_set_type does work\n");
		dia = 1;
	}
	if (0 != pkt_set_type(pkt, 0b01)) {
		printf("Test1 : pkt_set_type does work\n");
		dia = 1;
	}
	if (0 != pkt_set_tr(pkt, 0b0)) {
		printf("Test1 : pkt_set_tr does work\n");
		dia = 1;
	}
	if (0 != pkt_set_window(pkt, 0b00101)) {
		printf("Test1 : pkt_set_window does work\n");
		dia = 1;
	}
	if (0 != pkt_set_seqnum(pkt, 12)) {
		printf("Test1 : pkt_set_seqnum does work\n");
		dia = 1;
	}
	if (0 != pkt_set_length(pkt, 5)) {
		printf("Test1 : pkt_set_length does work\n");
		dia = 1;
	}
	if (0 != pkt_set_timestamp(pkt, 227)) {
		printf("Test1 : pkt_set_timestamp does work\n");
		dia = 1;
	}
	if (0 != pkt_set_crc1(pkt, 55)) {
		printf("Test1 : pkt_set_crc1 does work\n");
		dia = 1;
	}
	if (0 != pkt_set_playload(pkt, "abcde", 5)) {
		printf("Test1 : pkt_set_playload does work\n");
		dia = 1;
	}
	if (0 != pkt_set_crc2(pkt, 72)) {
		printf("Test1 : pkt_set_crc2 does work\n");
		dia = 1;
	}
	pkt_del(pkt);
	if (pkt != NULL) {
		printf("Test1 : pkt_del does work\n");
		dia = 1;
	}
	return dia;
}
int test2() {
	struct pkt_t* pkt = pkt_new();
	int dia = pkt_set_type(pkt, 1);
	dia = pkt_set_tr(pkt, 0);
	dia = pkt_set_window(pkt, 5);
	dia = pkt_set_seqnum(pkt, 21);
	dia = pkt_set_length(pkt, 5);
	dia = pkt_set_timestamp(pkt, 222);
	dia = pkt_set_crc1(pkt, 55);
	dia = pkt_set_playload(pkt, "abcde", 5);
	dia = pkt_set_crc2(pkt, 66);
	if (dia != 0) {
		printf("Test2 : pkt_set_<> does work\n");
		pkt_del(pkt);
		return 1;

	}
	char *buf = malloc(5 * sizeof(char));
	if (buf == NULL) {
		printf("Test2 : no memory\n");
		pkt_del(pkt);
		return 1;
	}

	if (pkt_encode(pkt, buf, 5 * sizeof(char)) != 0) {
		printf("Test2 : pkt_encode doesn't work\n");
		pkt_del(pkt);
		free(buf);
		return 1;
	}
	if (pkt_decode(buf, 5 * sizeof(char), pkt) != 0) {
		printf("Test2 : pkt_decode doesn't work\n");
		pkt_del(pkt);
		free(buf);
		return 1;
	}
	free(buf);
	dia = 0;
	if (1 != pkt_get_type(pkt)) {
		printf("Test2 : type does match epected:1 get:%i\n", pkt_get_type(pkt));
		dia = 1;
	}
	if (0 != pkt_get_tr(pkt)) {
		printf("Test2 : tr does match epected:0 get:%i\n", pkt_get_tr(pkt));
		dia = 1;
	}
	if (5 != pkt_get_window(pkt)) {
		printf("Test2 : window does match epected:5 get:%i\n", pkt_get_window(pkt));
		dia = 1;
	}
	if (21 != pkt_get_seqnum(pkt)) {
		printf("Test2 : seqnum does match epected:21 get:%i\n", pkt_get_seqnum(pkt));
		dia = 1;
	}
	if (5 != pkt_get_length(pkt)) {
		printf("Test2 : length does match epected:5 get:%i\n", pkt_get_length(pkt));
		dia = 1;
	}
	if (222 != pkt_get_timestamp(pkt)) {
		printf("Test2 : timestamp does match epected:222 get:%i\n", pkt_get_timestamp(pkt));
		dia = 1;
	}
	if (55 != pkt_get_crc1(pkt)) {
		printf("Test2 : crc1 does match epected:55 get:%i\n", pkt_get_crc1(pkt));
		dia = 1;
	}
	if (66 != pkt_get_crc2(pkt)) {
		printf("Test2 : crc2 does match epected:66 get:%i\n", pkt_get_seqnum(pkt));
		dia = 1;
	}

	pkt_del(pkt);
	return dia;
}
int test3() {
	/*ToDo*/
	return 0;
}