#include "packet_interface.h" /*retire la interface*/

/* Extra #includes */
/* Your code will be inserted here */

struct __attribute__((__packed__)) pkt {
	ptypes_t type;
	uint8_t tr;
	uint8_t window;
	uint8_t seqnum;
	uint16_t length;
	uint32_t timestamp;
	uint32_t crc1;
	char * playload;
	uint32_t crc2;
};

/* Extra code */
/* Your code will be inserted here */

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
	}
	exit(EXIT_SUCCESS);
}

pkt_status_code pkt_decode(const char *data, const size_t len, pkt_t *pkt)
{
	/* Your code will be inserted here */
}

pkt_status_code pkt_encode(const pkt_t* pkt, char *buf, size_t *len)
{
	/* Your code will be inserted here */
}

ptypes_t pkt_get_type(const pkt_t* pkt)
{
	if (pkt == NULL) {
		
	}
	return plt->type;
}

uint8_t  pkt_get_tr(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return plt->tr;
}

uint8_t  pkt_get_window(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return plt->window;
}

uint8_t  pkt_get_seqnum(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return pl->seqnum;
}

uint16_t pkt_get_length(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return plt->length;
}

uint32_t pkt_get_timestamp(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return plt->timestamp;
}

uint32_t pkt_get_crc1(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return plt->crc1;
}

uint32_t pkt_get_crc2(const pkt_t* pkt)
{
	if (pkt == NULL) {

	}
	return plt->crc2;
}

const char* pkt_get_payload(const pkt_t* pkt)
{
	/* Your code will be inserted here */
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
	if ((pkt->type== PTYPE_DATA) && (tr!=0)) {
		return E_TR;}
	pkt->tr = tr;
	return 0;
}

pkt_status_code pkt_set_window(pkt_t *pkt, const uint8_t window)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((type < 0) || (type > 31)) {
		return E_WINDOW;}
	pkt->window = window;
	return 0;
}

pkt_status_code pkt_set_seqnum(pkt_t *pkt, const uint8_t seqnum)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((type < 0) || (type > 255)) {
		return E_SEQNUM;}
	pkt->seqnum = seqnum;
	return 0;
}

pkt_status_code pkt_set_length(pkt_t *pkt, const uint16_t length)
{
	if (pkt == NULL) {
		return E_UNCONSISTENT;}
	if ((type < 0) || (type > 512)) {
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
	/* Your code will be inserted here */
}
