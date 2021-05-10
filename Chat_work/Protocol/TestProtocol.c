/*
gcc -ansi -pedantic -Wall Protocol.c TestProtocol.c -o TestProtocol.out
*/

#include "../mu_test.h"
#include "Protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


UNIT(protocol_unpact_first_byt)
	
    char *userName = "Magi"; 
    char *password = "123456";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizePassword = (int)(strlen(password)+1);
    char *packet= malloc(sizeUserName+sizePassword+3);
    char missionUnpacket[1];
    char mission[1];
    size_t sizePacket = ProtocolRegistrationPack(userName, password, packet);
    ASSERT_THAT(sizePacket == sizePassword+sizeUserName+3);
    ProtocolFirstBytUnpack(packet, missionUnpacket);
    mission[0]=packet[0];
	ASSERT_THAT(strcmp(missionUnpacket, mission) == 0);
    free(packet);
    

END_UNIT

/**************************** registration************************************/

UNIT(protocol_registration_pack_working)
	
    char *userName = "Magi"; 
    char *password = "123456";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizePassword = (int)(strlen(password)+1);
    char *packet= malloc(sizeUserName+sizePassword+3);
    size_t sizePacket = ProtocolRegistrationPack(userName, password, packet);
	ASSERT_THAT(sizePacket == (sizePassword+sizeUserName+3));
    free(packet);

END_UNIT

UNIT(protocol_registration_un_pack_working)
	
    char userNameUnpack[20];
    char passwordUnpack[20];
    char *userName = "Magi"; 
    char *password = "123456";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizePassword = (int)(strlen(password)+1);
    int sizezPacket = sizePassword+sizeUserName+3;
    char *packet= (char*)malloc(sizezPacket*sizeof(char));
    size_t sizePacket = ProtocolRegistrationPack(userName, password, packet);
    ASSERT_THAT(sizezPacket == sizePacket);
    ProtocolRegistrationUnpack(userNameUnpack, passwordUnpack, packet);
	ASSERT_THAT(strcmp(userName,userNameUnpack) == 0);
    ASSERT_THAT(strcmp(password,passwordUnpack) == 0);
    free(packet);

END_UNIT

UNIT(protocol_confirm_registration_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmRegistrationPack(confirm,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+2));
    free(packet);

END_UNIT

UNIT(protocol_confirm_registration_un_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *confirmUnpacke = malloc(sizeConfirm);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmRegistrationPack(confirm,packet);
    ASSERT_THAT(sizePacket == sizeConfirm+2);
    ProtocolConfirmRegistrationUnpack( confirmUnpacke, packet);
	ASSERT_THAT(strcmp(confirm, confirmUnpacke) == 0);
    free(confirmUnpacke);
    free(packet);

END_UNIT
/************************finish registration************************************/
/**************************login***************************************/
UNIT(protocol_login_pack_working)
	
    char *userName = "Magi"; 
    char *password = "123456";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizePassword = (int)(strlen(password)+1);
    char *packet= malloc(sizeUserName+sizePassword+3);
    size_t sizePacket = ProtocolLoginPack(userName, password, packet);
	ASSERT_THAT(sizePacket == (sizePassword+sizeUserName+3));
    free(packet);

END_UNIT

UNIT(protocol_login_un_pack_working)
	
    char userNameUnpack[20];
    char passwordUnpack[20];
    char *userName = "Magi"; 
    char *password = "123456";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizePassword = (int)(strlen(password)+1);
    int sizezPacket = sizePassword+sizeUserName+3;
    char *packet= (char*)malloc(sizezPacket*sizeof(char));
    size_t sizePacket = ProtocolLoginPack(userName, password, packet);
    ASSERT_THAT(sizePacket == sizePacket);
    ProtocolLoginUnpack(userNameUnpack, passwordUnpack, packet);
	ASSERT_THAT(strcmp(userName,userNameUnpack) == 0);
    ASSERT_THAT(strcmp(password,passwordUnpack) == 0);
    free(packet);

END_UNIT

UNIT(protocol_confirm_login_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmLoginPack(confirm,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+2));
    free(packet);

END_UNIT

UNIT(protocol_confirm_login_un_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *confirmUnpacke = malloc(sizeConfirm);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmLoginPack(confirm,packet);
    ASSERT_THAT(sizePacket == sizeConfirm+2);
    ProtocolConfirmLoginUnpack( confirmUnpacke, packet);
	ASSERT_THAT(strcmp(confirm, confirmUnpacke) == 0);
    free(confirmUnpacke);
    free(packet);

END_UNIT
/************************finish login************************************/

/**************************join group***************************************/
UNIT(protocol_join_group_pack_working)
	
    char *groupName = "Daniel"; 
    char *userName = "magi";
    int sizeGroupName = (int)(strlen(groupName)+1);
    int sizeUserName = (int)(strlen(userName)+1);
    char *packet= malloc(sizeGroupName+sizeUserName+3);
    size_t sizePacket = ProtocolJoinGroupPack(groupName, userName, packet);
	ASSERT_THAT(sizePacket == (sizeGroupName+sizeUserName+3));
    free(packet);

END_UNIT

UNIT(protocol_join_group_un_pack_working)
	
    char userNameUnpack[20];
    char groupNameUnpack[20];
    char *userName = "Magi"; 
    char *groupName = "Daniel";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizeGroupName = (int)(strlen(groupName)+1);
    int sizezPacket = sizeGroupName+sizeUserName+3;
    char *packet= (char*)malloc(sizezPacket*sizeof(char));
    size_t sizePacket = ProtocolJoinGroupPack( groupName, userName, packet);
    ASSERT_THAT(sizePacket == sizezPacket);
    ProtocolJoinGroupUnpack(groupNameUnpack,userNameUnpack, packet);
	ASSERT_THAT(strcmp(userName,userNameUnpack) == 0);
    ASSERT_THAT(strcmp(groupName,groupNameUnpack) == 0);
    free(packet);

END_UNIT

UNIT(protocol_confirm_join_group_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmJoinGroupPack(confirm,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+2));
    free(packet);

END_UNIT

UNIT(protocol_confirm_join_group_un_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *confirmUnpacke = malloc(sizeConfirm);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmJoinGroupPack(confirm,packet);
    ASSERT_THAT(sizePacket == sizeConfirm+2);
    ProtocolConfirmJoinGroupUnpack( confirmUnpacke, packet);
	ASSERT_THAT(strcmp(confirm, confirmUnpacke) == 0);
    free(confirmUnpacke);
    free(packet);

END_UNIT
/************************finish join group************************************/


/**************************leave group***************************************/
UNIT(protocol_leave_group_pack_working)
	
    char *groupName = "Daniel"; 
    char *userName = "magi";
    int sizeGroupName = (int)(strlen(groupName)+1);
    int sizeUserName = (int)(strlen(userName)+1);
    char *packet= malloc(sizeGroupName+sizeUserName+3);
    size_t sizePacket = ProtocolLeaveGroupPack(groupName, userName, packet);
	ASSERT_THAT(sizePacket == (sizeGroupName+sizeUserName+3));
    free(packet);

END_UNIT

UNIT(protocol_leave_group_un_pack_working)
	
    char userNameUnpack[20];
    char groupNameUnpack[20];
    char *userName = "Magi"; 
    char *groupName = "Daniel";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizeGroupName = (int)(strlen(groupName)+1);
    int sizezPacket = sizeGroupName+sizeUserName+3;
    char *packet= (char*)malloc(sizezPacket*sizeof(char));
    size_t sizePacket = ProtocolLeaveGroupPack( groupName, userName, packet);
    ASSERT_THAT(sizePacket == sizePacket);
    ProtocolLeaveGroupUnpack(groupNameUnpack,userNameUnpack, packet);
	ASSERT_THAT(strcmp(userName,userNameUnpack) == 0);
    ASSERT_THAT(strcmp(groupName,groupNameUnpack) == 0);
    free(packet);

END_UNIT

UNIT(protocol_confirm_leave_group_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmLeaveGroupPack(confirm,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+2));
    free(packet);

END_UNIT

UNIT(protocol_confirm_leave_group_un_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *confirmUnpacke = malloc(sizeConfirm);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmLeaveGroupPack(confirm,packet);
    ASSERT_THAT(sizePacket == sizeConfirm+2);
    ProtocolConfirmLeaveGroupUnpack( confirmUnpacke, packet);
	ASSERT_THAT(strcmp(confirm, confirmUnpacke) == 0);
    free(confirmUnpacke);
    free(packet);

END_UNIT
/************************finish leave group************************************/

/**************************create group***************************************/



UNIT(protocol_create_group_pack_working)
	
    char *groupName = "Daniel"; 
    char *userName = "magi";
    int sizeGroupName = (int)(strlen(groupName)+1);
    int sizeUserName = (int)(strlen(userName)+1);
    char *packet= malloc(sizeGroupName+sizeUserName+3);
    size_t sizePacket = ProtocolCreateGroupPack(groupName, userName, packet);
	ASSERT_THAT(sizePacket == (sizeGroupName+sizeUserName+3));
    free(packet);

END_UNIT

UNIT(protocol_create_group_un_pack_working)
	
    char userNameUnpack[20];
    char groupNameUnpack[20];
    char *userName = "Magi"; 
    char *groupName = "Daniel";
    int sizeUserName = (int)(strlen(userName)+1);
    int sizeGroupName = (int)(strlen(groupName)+1);
    int sizezPacket = sizeGroupName+sizeUserName+3;
    char *packet= (char*)malloc(sizezPacket*sizeof(char));
    size_t sizePacket = ProtocolCreateGroupPack( groupName, userName, packet);
    ASSERT_THAT(sizePacket == sizezPacket);
    ProtocolCreateGroupUnpack(groupNameUnpack,userNameUnpack, packet);
	ASSERT_THAT(strcmp(userName,userNameUnpack) == 0);
    ASSERT_THAT(strcmp(groupName,groupNameUnpack) == 0);
    free(packet);

END_UNIT


UNIT(protocol_confirm_create_group_pack_working)
	
    char *confirm = "TRUE";
    char *ipMulticast="123";
    char *port = "345";
    int sizeConfirm = (int)(strlen(confirm)+1);
    int sizeIpMulticast = (int)(strlen(ipMulticast)+1);
    int sizePort = (int)(strlen(port)+1);
    char *packet= malloc(sizeConfirm+sizePort+sizeIpMulticast+4);
    size_t sizePacket = ProtocolConfirmCreateGroupPack(confirm,ipMulticast,port,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+sizeIpMulticast+sizePort+4));
    free(packet);

END_UNIT


UNIT(protocol_confirm_create_group_un_pack_working)
	
    char *confirm = "TRUE";
    char *ipMulticast="123";
    char *port = "345";
    int sizeConfirm = (int)(strlen(confirm)+1);
    int sizeIpMulticast = (int)(strlen(ipMulticast)+1);
    int sizePort = (int)(strlen(port)+1);
    char *confirmUnpacke = (char*)malloc(sizeConfirm*sizeof(char));
    char *ipMulticastUnpack=(char*)malloc(sizeIpMulticast*sizeof(char));
    char *portUnpack=(char*)malloc(sizePort*sizeof(char));
    char *packet= malloc(sizeConfirm+sizePort+sizeIpMulticast+4);
    size_t sizePacket = ProtocolConfirmCreateGroupPack(confirm,ipMulticast,port,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+sizeIpMulticast+sizePort+4));
    ProtocolConfirmCreateGroupUnpack(confirmUnpacke,ipMulticastUnpack,portUnpack,packet);
    ASSERT_THAT(strcmp(confirm, confirmUnpacke) == 0);
    ASSERT_THAT(strcmp(ipMulticast, ipMulticastUnpack) == 0);
    ASSERT_THAT(strcmp(port, portUnpack) == 0);
    free(packet);
    free(confirmUnpacke);
    free(ipMulticastUnpack);
    free(portUnpack);

END_UNIT


/************************finish create group************************************/

/**************************get list group***************************************/
UNIT(protocol_get_list_pack_working)
	
    char *packet= malloc(1);
    size_t sizePacket = ProtocolGetListPack( packet);
	ASSERT_THAT(sizePacket == 1);
    free(packet);

END_UNIT

UNIT(protocol_confirm_get_list_pack_working)
	
    char* groupNames = "Daniel, Rinat";
    int sizeGroupNames = (int)(strlen(groupNames)+1);
    char *packet= malloc(sizeGroupNames+2);
    size_t sizePacket = ProtocolConfirmGetListPack(groupNames,packet);
	ASSERT_THAT(sizePacket == (sizeGroupNames+2));
    free(packet);

END_UNIT

UNIT(protocol_confirm_get_list_un_pack_working)
	
    
    char* groupNames = "Daniel, Rinat";
    int sizeGroupNames = (int)(strlen(groupNames)+1);
    char *packet= malloc(sizeGroupNames+2);
    size_t sizePacket = ProtocolConfirmGetListPack(groupNames,packet);
    char *groupNameUnpacke = malloc(sizeGroupNames);
    ASSERT_THAT(sizePacket == sizeGroupNames+2);
    ProtocolConfirmGetListUnpack( groupNameUnpacke, packet);
	ASSERT_THAT(strcmp(groupNames, groupNameUnpacke) == 0);
    free(groupNameUnpacke);
    free(packet);

END_UNIT
/************************finish get list group************************************/


/**************************log out group***************************************/
UNIT(protocol_log_out_pack_working)
	
    char *packet= malloc(1);
    size_t sizePacket = ProtocolLogOutPack( packet);
	ASSERT_THAT(sizePacket == 1);
    free(packet);

END_UNIT

UNIT(protocol_confirm_log_out_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmLogOutPack(confirm,packet);
	ASSERT_THAT(sizePacket == (sizeConfirm+2));
    free(packet);

END_UNIT

UNIT(protocol_confirm_log_out_un_pack_working)
	
    char* confirm = "TRUE";
    int sizeConfirm = (int)(strlen(confirm)+1);
    char *confirmUnpacke = malloc(sizeConfirm);
    char *packet= malloc(sizeConfirm+2);
    size_t sizePacket = ProtocolConfirmLogOutPack(confirm,packet);
    ASSERT_THAT(sizePacket == sizeConfirm+2);
    ProtocolConfirmLogOutUnpack( confirmUnpacke, packet);
	ASSERT_THAT(strcmp(confirm, confirmUnpacke) == 0);
    free(confirmUnpacke);
    free(packet);

END_UNIT

/************************finish get list group************************************/


/*******************************************************************/
TEST_SUITE(Protocol)

	TEST(protocol_unpact_first_byt)
    
    TEST(protocol_registration_pack_working)
	TEST(protocol_registration_un_pack_working)
    TEST(protocol_confirm_registration_pack_working)
    TEST(protocol_confirm_registration_un_pack_working)


    TEST(protocol_login_pack_working)
    TEST(protocol_login_un_pack_working)
    TEST(protocol_confirm_login_pack_working)
    TEST(protocol_confirm_login_un_pack_working)


    TEST(protocol_join_group_pack_working)
    TEST(protocol_join_group_un_pack_working)
    TEST(protocol_confirm_join_group_pack_working)
    TEST(protocol_confirm_join_group_un_pack_working)


    TEST(protocol_leave_group_pack_working)
    TEST(protocol_leave_group_un_pack_working)
    TEST(protocol_confirm_leave_group_pack_working)
    TEST(protocol_confirm_leave_group_un_pack_working)


    TEST(protocol_create_group_pack_working)
    TEST(protocol_create_group_un_pack_working)
    TEST(protocol_confirm_create_group_pack_working)
    TEST(protocol_confirm_create_group_un_pack_working)

    TEST(protocol_get_list_pack_working)
    TEST(protocol_confirm_get_list_pack_working)
    TEST(protocol_confirm_get_list_un_pack_working)


    TEST(protocol_log_out_pack_working)
    TEST(protocol_confirm_log_out_pack_working)
    TEST(protocol_confirm_log_out_un_pack_working)


END_SUITE













