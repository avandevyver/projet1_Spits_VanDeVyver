#include "packet.h"

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

/* Extra #includes */
/* Your code will be inserted here */

struct __attribute__((__packed__)) pkt {
	uint8_t window : 5;
	uint8_t tr : 1;
	ptypes_t type : 2;
	uint8_t seqnum;
	uint16_t length;

	uint32_t timestamp;

	uint32_t crc1;
	char * playload;
	uint32_t crc2;
};

pkt_status_code pkt_validity(const pkt_t *pkt) {
	if (pkt == NULL) {
		return E_UNCONSISTENT;
	}
	if ((pkt->type < 1) || (pkt->type > 3)) {
		return E_TYPE;
	}
	if ((pkt->tr != 1) || (pkt->tr != 0)) {
		return E_TR;
	}
	if ((pkt->type == PTYPE_DATA) && (pkt->tr != 0)) {
		return E_TR;
	}
	if ((pkt->window < 0) || (pkt->window > 31)) {
		return E_WINDOW;
	}
	if ((pkt->seqnum < 0) || (pkt->seqnum > 255)) {
		return E_SEQNUM;
	}
	if ((pkt->length < 0) || (pkt->length > 512)) {
		return E_LENGTH;
	}
	return 0;
}

pkt_t* pkt_new()
{
	struct pkt_t* pkt = malloc(sizeof(struct pkt_t*));
	return pkt;
}

void pkt_del(pkt_t *pkt)
{
	if (pkt != NULL) {
		if (pkt->playload != NULL) {
			free(pkt->playload);
		}
		free(pkt);
	}
	exit(EXIT_SUCCESS);
}

pkt_status_code pkt_decode(const char *data, const size_t len, pkt_t *pkt)
{
	if (len < 12 * sizeof(char)) {
		return E_NOHEADER;
	}
	if (pkt == NULL) {
		pkt = pkt_new();
		if (pkt == NULL) {
			return E_NOMEM;
		}
	}
	memcpy(pkt, data, 12 * sizeof(char));/*copy header*/
	pkt->length = ntohs(pkt->length);
	if ((len != 12 * sizeof(char)) || (len != (16 + pkt->length) * sizeof(char))) {
		return E_UNCONSISTENT;
	}
	pkt->playload = malloc(pkt->length * sizeof(char));
	if (pkt->playload == NULL) {
		return E_NOMEM;
	}
	pkt->crc1 = ntohl(pkt->crc1);

	char * tmp = &(data[12]);
	memcpy(pkt->playload, tmp, pkt->length * sizeof(char));
	tmp = &(tmp[pkt->length]);
	memcpy(&(pkt->crc2), tmp, 4 * sizeof(char));
	pkt->crc2 = ntohl(pkt->crc2);

	/*calc crc1 crc2 + check*/

	return pkt_validity(pkt);
}

pkt_status_code pkt_encode(const pkt_t* pkt, char *buf, size_t *len)
{
	pkt_status_code dia = pkt_validity(pkt);
	if (dia != 0) {
		return dia;
	}

	int pkt_size = 12 + pkt->length;
	if (pkt->length != 0) {
		pkt_size += 4;
	}
	if (len < pkt_size * sizeof(char)) {
		return E_NOMEM;
	}

	memcpy(buf, pkt, 2);/*copy type-tr-window*/
	char * tmp = &(buf[2]);
	memcpy(buf, &(htons(pkt->length)), 2 * sizeof(char));
	tmp = &(tmp[2]);
	memcpy(buf, &(pkt->timestamp), 4 * sizeof(char));
	tmp = &(tmp[4]);
	/*calc crc1*/
	memcpy(tmp, &(htonl(pkt->crc1)), 4 * sizeof(char));
	tmp = &(tmp[4]);
	if (l > 0) {
		/*calc crc2*/
		memcpy(tmp, pkt->playload, pkt->length * sizeof(char));
		tmp = &(tmp[pkt->length]);
		memcpy(tmp, &(htons(pkt->crc2)), 4 * sizeof(char));
	}
	return 0;
}

ptypes_t pkt_get_type(const pkt_t* pkt)
{
	return plt->type;
}

uint8_t  pkt_get_tr(const pkt_t* pkt)
{
	return plt->tr;
}

uint8_t  pkt_get_window(const pkt_t* pkt)
{
	return plt->window;
}

uint8_t  pkt_get_seqnum(const pkt_t* pkt)
{
	return pl->seqnum;
}

uint16_t pkt_get_length(const pkt_t* pkt)
{
	return plt->length;
}

uint32_t pkt_get_timestamp(const pkt_t* pkt)
{
	return plt->timestamp;
}

uint32_t pkt_get_crc1(const pkt_t* pkt)
{
	return plt->crc1;
}

uint32_t pkt_get_crc2(const pkt_t* pkt)
{
	if (pkt->length == 0) {
		return 0;}
	return plt->crc2;
}

const char* pkt_get_payload(const pkt_t* pkt)
{
	if (pkt == NULL) {
		return NULL;}
	if (pkt->length == 0) {
		return NULL;}
	return pkt->playload;
}


pkt_status_code pkt_set_type(pkt_t *pkt, const ptypes_t type)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((type < 1) || (type > 3)) {
		return E_TYPE;}
	pkt->type = type;
	return 0;
}

pkt_status_code pkt_set_tr(pkt_t *pkt, const uint8_t tr)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((tr != 1) || (tr != 0)) {
		return E_TR;}
	if ((pkt->type == PTYPE_DATA) && (tr != 0)) {
		return E_TR;}
	pkt->tr = tr;
	return 0;
}

pkt_status_code pkt_set_window(pkt_t *pkt, const uint8_t window)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((window < 0) || (window > 31)) {
		return E_WINDOW;}
	pkt->window = window;
	return 0;
}

pkt_status_code pkt_set_seqnum(pkt_t *pkt, const uint8_t seqnum)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((seqnum < 0) || (seqnum > 255)) {
		return E_SEQNUM;}
	pkt->seqnum = seqnum;
	return 0;
}

pkt_status_code pkt_set_length(pkt_t *pkt, const uint16_t length)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((length < 0) || (length > 512)) {
		return E_LENGTH;}
	pkt->length = length;
	return 0;
}

pkt_status_code pkt_set_timestamp(pkt_t *pkt, const uint32_t timestamp)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	pkt->timestamp = timestamp;
	return 0;
}

pkt_status_code pkt_set_crc1(pkt_t *pkt, const uint32_t crc1)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	pkt->crc1 = crc1;
	return 0;
}

pkt_status_code pkt_set_crc2(pkt_t *pkt, const uint32_t crc2)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	pkt->crc2 = crc2;
	return 0;
}

pkt_status_code pkt_set_payload(pkt_t *pkt,
	const char *data,const uint16_t length)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}

	if (pkt_set_length(pkt , length) != 0) {
		return E_LENGTH;
	}
	if ((data == NULL) || (length == 0)) {
		pkt_del(pkt);
		return 0;
	}
	char* load = malloc(n * sizeof(char*));
	if (load == NULL) {
		return E_NOMEM;}
	load = strcpy(load, buf);
	pkt_del(pkt);
	pkt->playload = load;
	return 0;
}
