"projet1_Spits_VanDeVyver"
Projet n°1 du cours INGI 1341 Réseau 

== SENDER ==
* Connection
creation socket
connect / bind

** Envoye DATA
encode(stocké dans buffer) et envoyer

if(reception ACK)
{actualise <time> & <window>
evalue les packet acquité en fonction de <seqnum_ack>
envoye en fonction de <window>}

if(reception NACK)
{renvoyer <seqnum_nack>}

if(no answer)
{retransmisstion apres <time> ms}

== RECEIVER ==
* Connection
attend une demande de connection
établie la connection

** Reception Data
decode
if(corrompu)
{send NACK}

if(manque un packet dans window)
{stock dans buffer}

if(Data attendu)
{delivre Data + buffer
send ACK <seqnum_last_elme deliver>}

if(No answer)
{retransmission ACK <seqnum_last_elme deliver>}