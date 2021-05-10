#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdlib.h> /*size_t*/
typedef enum Mission
{
    REGESTRATION,
	LOGIN,
	CREATE_GROUP,
	JOIN_GROUP,
	LEAVE_GROUP,
	GET_LIST,
	LOG_OUT
} Mission;

/*
Description:The function returns the first byte of the operation to be performed.
Input: get the packet and place to the first byte
Output:NONE.
Error:NONE.
*/
void ProtocolFirstBytUnpack(char *_packet, char *_mission);
/******************************registration************************************/
/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent.
Input:user name and password and packet to pack all things.
Output: rsturn the size the packet to send.
Error:NONE.
*/
size_t ProtocolRegistrationPack(const char *_userName, const char *_password, char *_packet); 

/* 
server -> protocol (unpack)
Description:The server sends to the protocol that will open for him the package he received.
Input:get place the user name and place the password and the packet to open.
Output:NONE.
Error:NONE.
*/
void ProtocolRegistrationUnpack(char *_userName, char *_password, char *_packet);/*s->p*/

/*
server->protocol(pack)
Description:The server sends to the protocol that will pack the message of the operation after it has performed the operation.
Input:get confirm and packet to pack the confirm.
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmRegistrationPack(char *_confirm, char *_packet);/*s->p*/

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return the answer from the server.
Input: get the packet and place to return the confirm from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmRegistrationUnpack( char *_confirm, char *_packet);/*c->p*/
/************************finish registration************************************/
/**************************login************************************/
/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent.
Input:user name and password and packet to pack all things.
Output: rsturn the size the packet to send.
Error:NONE.
*/
size_t ProtocolLoginPack(const char *_userName, const char *_password, char *_packet);

/* 
server -> protocol (unpack)
Description:The server sends to the protocol that will open for him the package he received.
Input:get place the user name and place the password and the packet to open.
Output:NONE.
Error:NONE.
*/
void ProtocolLoginUnpack(char *_userName, char *_password, char *_packet);

/*
server->protocol(pack)
Description:The server sends to the protocol that will pack the message of the operation after it has performed the operation.
Input:get confirm and packet to pack the confirm.
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmLoginPack(char *_confirm, char *_packet);

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return the answer from the server.
Input: get the packet and place to return the confirm from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmLoginUnpack( char *_confirm, char *_packet);
/************************finish login************************************/
/**************************join group***************************************/
/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent.
Input:user name and anme group and packet to pack all things.
Output: rsturn the size the packet to send.
Error:NONE.
*/
size_t ProtocolJoinGroupPack(const char *_groupName, const char *_userName, char *_packet);

/* 
server -> protocol (unpack)
Description:The server sends to the protocol that will open for him the package he received.
Input:get place the user name and place the group name and the packet to open.
Output:NONE.
Error:NONE.
*/
void ProtocolJoinGroupUnpack(char *_groupName, char *_userName, char *_packet);

/*
server->protocol(pack)
Description:The server sends to the protocol that will pack the message of the operation after it has performed the operation and return the port and ipMlticast.
Input:get confirm and packet to pack the confirm and get ipMulticast and port to pack in packet
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmJoinGroupPack(char *_confirm, char *_ipMulticast, char *_port,char *_packet);

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return the answer from the server and ipMulticast and port.
Input: get the packet and place to return the confirm, and place to ipMulticast and place to port from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmJoinGroupUnpack(char *_confirm, char *_ipMulticast, char *_port,char *_packet);

/************************finish join group************************************/
/**************************leave group***************************************/

/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent.
Input:user name and anme group and packet to pack all things.
Output: rsturn the size the packet to send.
Error:NONE.
*/
size_t ProtocolLeaveGroupPack(const char *_groupName, const char *_userName, char *_packet);

/* 
server -> protocol (unpack)
Description:The server sends to the protocol that will open for him the package he received.
Input:get place the user name and place the group name and the packet to open.
Output:NONE.
Error:NONE.
*/
void ProtocolLeaveGroupUnpack(char *_groupName, char *_userName, char *_packet);

/*
server->protocol(pack)
Description:The server sends to the protocol that will pack the message of the operation after it has performed the operation.
Input:get confirm and packet to pack the confirm.
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmLeaveGroupPack(char *_confirm, char *_packet);

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return the answer from the server.
Input: get the packet and place to return the confirm from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmLeaveGroupUnpack( char *_confirm, char *_packet);
/************************finish leave group************************************/
/**************************create group***************************************/
/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent.
Input:user name and anme group and packet to pack all things.
Output: rsturn the size the packet to send.
Error:NONE.
*/
size_t ProtocolCreateGroupPack(const char *_groupName,const char *_userName, char *_packet);

/* 
server -> protocol (unpack)
Description:The server sends to the protocol that will open for him the package he received.
Input:get place the user name and place the group name and the packet to open.
Output:NONE.
Error:NONE.
*/
void ProtocolCreateGroupUnpack(char *_groupName,char *_userName, char *_packet);

/*
server->protocol(pack)
Description:The server sends to the protocol that will pack the message of the operation after it has performed the operation and return the port and ipMlticast.
Input:get confirm and packet to pack the confirm and get ipMulticast and port to pack in packet
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmCreateGroupPack(char *_confirm, char *_ipMulticast, char *_port,char *_packet);

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return the answer from the server and ipMulticast and port.
Input: get the packet and place to return the confirm, and place to ipMulticast and place to port from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmCreateGroupUnpack( char *_confirm, char *_ipMulticast, char *_port,char *_packet);
/************************finish create group************************************/
/**************************get list group***************************************/

/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent. Sends the task to be done.
Input:packet to pack the task to do.
Output:size the packet.
Error:NONE.
*/
size_t ProtocolGetListPack( char *_packet);
/*
server->protocol(pack)
Description:The function packs all the names of the groups that are currently in the system.
Input:get group names and packet to pack the group names.
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmGetListPack(char* _groupNames, char *_packet);

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return group names that are currently in the system.
Input: get the packet and place to return the group names from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmGetListUnpack( char *_groupNames, char *_packet);
/************************finish list group************************************/
/**************************log out ***************************************/

/*
client->protocol (pack)
Description:The client sends to the server. the protocol packs the things that are sent.
Input:user name and packet to pack the things.
Output: rsturn the size the packet to send.
Error:NONE.
*/
size_t ProtocolLogOutPack(char *_userName, char *_packet);

/* 
server -> protocol (unpack)
Description:The server sends to the protocol that will open for him the package he received.
Input:get place the user name and the packet to open.
Output:NONE.
Error:NONE.
*/
void ProtocolLogOutUnPack(char *_userName,  char *_packet);

/*
server->protocol(pack)
Description:The server sends to the protocol that will pack the message of the operation after it has performed the operation.
Input:get confirm and packet to pack the confirm.
Output:size the packet
Error: NONE.
*/
size_t ProtocolConfirmLogOutPack(char *_confirm, char *_packet);

/*
client->protocol(unpack)
Description:The Client sends to the protocol the package he received that will open it and return the answer from the server.
Input: get the packet and place to return the confirm from server
Output: NONE.
Error:NONE.
*/
void ProtocolConfirmLogOutUnpack(char *_confirm, char *_packet);
/************************finish log out***********************************/



#endif/*PROTOCOL*/