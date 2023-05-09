#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

/**
 * The protocol uses hexadecimal numbers to identify the type of message.
 * The size of messages is: int type
 */

#define SERVER_CONN 0x01
#define SERVER_CONN_REJECTION 0x02
#define SERVER_SEND_MESSAGE 0x03
#define SERVER_RECV_MESSAGE 0x04

#define CLIENT_CONN 0x11
#define CLIENT_DISCONNECTION 0x12
#define CLIENT_SEND_MESSAGE 0x13
#define CLIENT_RECV_MESSAGE 0x14

#endif // !_PROTOCOL_H_