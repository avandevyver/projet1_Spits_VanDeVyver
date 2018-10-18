#include "packet.h"

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <zlib.h>

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
		return E_TYPE;   /** Type   match range **/
	}
	if ((pkt->tr != 1) && (pkt->tr != 0)) {
		return E_TR;     /** Tr     match range **/
	}
	if ((pkt->type == PTYPE_DATA) && (pkt->tr != 0)) {
		return E_TR;     /** Tr     match       **/
	}
	if ((pkt->window < 0) || (pkt->window > 31)) {
		return E_WINDOW; /** Window match range **/
	}
	if ((pkt->seqnum < 0) || (pkt->seqnum > 255)) {
		return E_SEQNUM; /** Seqnum match range **/
	}
	if ((pkt->length < 0) || (pkt->length > 512)) {
		return E_LENGTH; /** Length match range **/
	}
	return 0;
}

pkt_t* pkt_new()
{
	struct pkt_t* pkt = malloc(sizeof(struct pkt_t*));
	if (pkt != NULL) {
		pkt->type = 0;
		pkt->tr = 0;
		pkt->window = 0;
		pkt->seqnum = 0;
		pkt->length = 0;
		pkt->timestamp = 0;
		pkt->crc1 = 0;
		pkt->playload = NULL;
		pkt->crc2 = 0;
	}
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
	/** Check size data **/
	if (len < 12 * sizeof(char)) {
		return E_NOHEADER;
	}
	/** Prevente NULL Pointer exeption**/
	if (pkt == NULL) {
		pkt = pkt_new();
		if (pkt == NULL) {
			return E_NOMEM;
		}
	}
	else if (pkt->playload != NULL) {
		free(pkt->playload);
	}
	/**== Copy Header ==**/
	memcpy(pkt, data, 12 * sizeof(char));
	pkt->length = ntohs(pkt->length);
	pkt->crc1 = ntohl(pkt->crc1);
	/** Check validity header **/
	pkt_status_code dia = pkt_validity(pkt);
	if (dia != 0) {
		return dia;
	}
	/** Check size data **/
	if ((len != 12 * sizeof(char)) || (len < (16 + pkt->length) * sizeof(char))) {
		return E_UNCONSISTENT;
	}
	/** Check CRC 1 **/
	if (pkt->tr == 0) {
		if (pkt->crc1 != crc32(0, data, 8 * sizeof(char))) {
			return E_CRC;
		}
	}
	/**== Carry playload ==**/
	if (len != 12 * sizeof(char)) {

		/** Copy Playload **/
		pkt->playload = malloc(pkt->length * sizeof(char));
		if (pkt->playload == NULL) {
			return E_NOMEM;
		}
		char * tmp = &(data[12]);
		memcpy(pkt->playload, tmp, pkt->length * sizeof(char));
		tmp = &(tmp[pkt->length]);
		memcpy(&(pkt->crc2), tmp, 4 * sizeof(char));
		pkt->crc2 = ntohl(pkt->crc2);
		/** Check CRC 2 **/
		if (pkt->tr == 0) {
			if (pkt->crc2 != crc32(0, pkt->playload, pkt->length * sizeof(char))) {
				return E_CRC;
			}
		}
	}

	return 0;
}

pkt_status_code pkt_encode(const pkt_t* pkt, char *buf, size_t *len)
{
	/** Check validity header **/
	pkt_status_code dia = pkt_validity(pkt);
	if (dia != 0) {
		return dia;
	}
	/** Size evaluation **/
	int pkt_size = 12 + pkt->length;
	if (pkt->length != 0) {
		pkt_size += 4;
	}
	if (len < pkt_size * sizeof(char)) {
		return E_NOMEM;
	}
	/**== Paste Header ==**/
	memcpy(buf, pkt, 2);                                  /* type-tr-window */
	char * tmp = &(buf[2]);
	memcpy(tmp, &(htons(pkt->length)), 2 * sizeof(char)); /*     length     */
	tmp = &(tmp[2]);
	memcpy(tmp, &(pkt->timestamp), 4 * sizeof(char));     /*    timestamp   */
	tmp = &(tmp[4]);
	/** Calcule crc 1 **/
	pkt->crc1 = crc32(0, buf, 8 * sizeof(char));
	memcpy(tmp, &(htonl(pkt->crc1)), 4 * sizeof(char));   /*     crc 1      */
	tmp = &(tmp[4]);

	/**== Carry playload ==**/
	if (l > 0) {
		/** Calcule crc 2 **/
		pkt->crc2 = crc32(0, pkt->playload, pkt->length * sizeof(char));
		memcpy(tmp, pkt->playload, pkt->length * sizeof(char)); /* playload */
		tmp = &(tmp[pkt->length]);
		memcpy(tmp, &(htons(pkt->crc2)), 4 * sizeof(char));     /*  crc 2   */
	}
	/** Bytes copy in buf**/
	len = pkt_size;
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
	if (pkt->playload != NULL) {
		free(pkt->playload);
	}
	pkt->playload = load;
	return 0;
}
