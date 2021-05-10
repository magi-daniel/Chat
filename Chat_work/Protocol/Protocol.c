#include <stdio.h> /*NULL*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*strlen*/
#include "Protocol.h"

/**********************************help func******************************************/
static size_t ProtocolTwoParametersPack(const char *_parameter1, const char *_parameter2, char *_packet);
static void ProtocolTwoParametersUnpack(char *_parameter1, char *_parameter2, char *_packet);
static size_t ProtocolConfirmOneParameterPack(char *_parameter1, char *_packet);
static void ProtocolConfirmOneParameterUnpack( char *_parameter1, char *_packet);
static size_t ProtocolConfirmThreeParameterPack(char *_parameter1,char *_parameter2, char *_parameter3, char *_packet);
static void ProtocolConfirmThreeParameterUnpack(char *_parameter1,char *_parameter2, char *_parameter3, char *_packet);
static size_t ProtocolOneParametersPack(const char *_parameter1, char *_packet);
static void ProtocolOneParametersUnpack(char *_parameter1, char *_packet);
/********************************finish help func****************************************/

void ProtocolFirstBytUnpack(char *_packet, char *_mission)
{
    _mission[0] = (char)_packet[0];
    _mission[1]='\0';
}
/**************************** registration************************************/
size_t ProtocolRegistrationPack(const char *_userName, const char *_password, char *_packet)
{

    _packet[0] = (char)REGESTRATION;
    return ProtocolTwoParametersPack(_userName, _password, _packet);
}


void ProtocolRegistrationUnpack(char *_userName, char *_password, char *_packet)
{
    ProtocolTwoParametersUnpack(_userName, _password, _packet);
}

size_t ProtocolConfirmRegistrationPack(char *_confirm, char *_packet)
{
    _packet[0]=(char)REGESTRATION;
    return ProtocolConfirmOneParameterPack(_confirm, _packet);
}

void ProtocolConfirmRegistrationUnpack( char *_confirm, char *_packet)
{
    ProtocolConfirmOneParameterUnpack( _confirm, _packet);
}
/************************finish registration************************************/
/**************************login***************************************/
size_t ProtocolLoginPack(const char *_userName, const char *_password, char *_packet)
{
    _packet[0] = (char)LOGIN;
    return ProtocolTwoParametersPack(_userName, _password, _packet);
}

void ProtocolLoginUnpack(char *_userName, char *_password, char *_packet)
{
    ProtocolTwoParametersUnpack(_userName, _password, _packet);
}

size_t ProtocolConfirmLoginPack(char *_confirm, char *_packet)
{
    _packet[0]=(char)LOGIN;
    return ProtocolConfirmOneParameterPack(_confirm, _packet);
}

void ProtocolConfirmLoginUnpack( char *_confirm, char *_packet)
{
    ProtocolConfirmOneParameterUnpack( _confirm, _packet);
}
/************************finish login************************************/
/**************************join group***************************************/
size_t ProtocolJoinGroupPack(const char *_groupName, const char *_userName, char *_packet)
{
    _packet[0] = (char)JOIN_GROUP;
    return ProtocolTwoParametersPack(_groupName, _userName, _packet);
}

void ProtocolJoinGroupUnpack(char *_groupName, char *_userName, char *_packet)
{
    ProtocolTwoParametersUnpack(_groupName, _userName, _packet);
}

size_t ProtocolConfirmJoinGroupPack(char *_confirm, char *_ipMulticast, char *_port,char *_packet)
{
    _packet[0]=(char)JOIN_GROUP;
    return ProtocolConfirmThreeParameterPack(_confirm,_ipMulticast,_port, _packet);
}


void ProtocolConfirmJoinGroupUnpack(char *_confirm, char *_ipMulticast, char *_port,char *_packet)
{
    ProtocolConfirmThreeParameterUnpack( _confirm, _ipMulticast, _port,_packet);
}

/************************finish join group************************************/
/**************************leave group***************************************/
size_t ProtocolLeaveGroupPack(const char *_groupName, const char *_userName, char *_packet)
{
    _packet[0] = (char)LEAVE_GROUP;
    return ProtocolTwoParametersPack(_groupName, _userName, _packet);
}

void ProtocolLeaveGroupUnpack(char *_groupName, char *_userName, char *_packet)
{
    ProtocolTwoParametersUnpack(_groupName, _userName, _packet);
}

size_t ProtocolConfirmLeaveGroupPack(char *_confirm, char *_packet)
{
    _packet[0]=(char)LEAVE_GROUP;
    return ProtocolConfirmOneParameterPack(_confirm, _packet);
}

void ProtocolConfirmLeaveGroupUnpack( char *_confirm, char *_packet)
{
    ProtocolConfirmOneParameterUnpack( _confirm, _packet);
}

/************************finish leave group************************************/
/**************************create group***************************************/

size_t ProtocolCreateGroupPack(const char *_groupName,const char *_userName, char *_packet)
{
    _packet[0] = (char)CREATE_GROUP;
    return ProtocolTwoParametersPack(_groupName, _userName,_packet);
}

void ProtocolCreateGroupUnpack(char *_groupName, char *_userName, char *_packet)
{
    ProtocolTwoParametersUnpack(_groupName, _userName,_packet);
}

size_t ProtocolConfirmCreateGroupPack(char *_confirm, char *_ipMulticast, char *_port,char *_packet)
{
    _packet[0]=(char)CREATE_GROUP;
    return ProtocolConfirmThreeParameterPack(_confirm,_ipMulticast,_port, _packet);
}

void ProtocolConfirmCreateGroupUnpack( char *_confirm, char *_ipMulticast, char *_port,char *_packet)
{
    ProtocolConfirmThreeParameterUnpack( _confirm, _ipMulticast, _port,_packet);
}
/************************finish create group************************************/
/**************************get list group***************************************/
size_t ProtocolGetListPack( char *_packet) /*c->s*/
{
    _packet[0] = (char)GET_LIST;
    return 1;
}

size_t ProtocolConfirmGetListPack(char* _groupNames, char *_packet)/*p->s*/
{
    _packet[0]=(char)GET_LIST;
    return ProtocolConfirmOneParameterPack(_groupNames, _packet);
}

void ProtocolConfirmGetListUnpack( char *_groupNames, char *_packet)/*c->p*/
{
    ProtocolConfirmOneParameterUnpack( _groupNames, _packet);
}
/************************finish list group************************************/
/**************************log out ***************************************/
size_t ProtocolLogOutPack(char *_userName, char *_packet)
{
    _packet[0] = (char)LOG_OUT;
    return ProtocolOneParametersPack( _userName,_packet);
}
void ProtocolLogOutUnPack(char *_userName,  char *_packet)
{
    ProtocolOneParametersUnpack(_userName,_packet);
}

size_t ProtocolConfirmLogOutPack(char *_confirm, char *_packet)
{
    _packet[0]=(char)LOG_OUT;
    return ProtocolConfirmOneParameterPack(_confirm, _packet);
}

void ProtocolConfirmLogOutUnpack( char *_confirm, char *_packet)
{
    ProtocolConfirmOneParameterUnpack( _confirm, _packet);
}
/************************finish log out***********************************/

/****************************help func****************************************/

static size_t ProtocolOneParametersPack(const char *_parameter1, char *_packet)
{
    char lenParameter1;
    lenParameter1= (char)(strlen(_parameter1)+1);
    _packet[1]=(char)(lenParameter1);
    strcpy(_packet+2, _parameter1);
    return ((size_t)(lenParameter1+2));
}


static size_t ProtocolTwoParametersPack(const char *_parameter1, const char *_parameter2, char *_packet)
{
    char lenParameter1, lenParameter2;
    lenParameter1= (char)(strlen(_parameter1)+1);
    lenParameter2= (char)(strlen(_parameter2)+1);
    _packet[1]=(char)(lenParameter1);
    strcpy(_packet+2, _parameter1);
    _packet[2+lenParameter1]=lenParameter2;
    strcpy(_packet+3+lenParameter1, _parameter2);
    return ((size_t)(lenParameter1+lenParameter2+3));
}



static void ProtocolTwoParametersUnpack(char *_parameter1, char *_parameter2, char *_packet)
{
    int lenParameter1 = (int)_packet[1];
    strcpy(_parameter1 ,_packet + 2);
    strcpy(_parameter2, _packet+3+lenParameter1);
}



static size_t ProtocolConfirmOneParameterPack(char *_parameter1, char *_packet)
{
    char lenparameter1;
    lenparameter1 = (char)strlen(_parameter1)+1;
    _packet[1]=lenparameter1;
    strcpy(_packet+2, _parameter1);
    return (lenparameter1+2);
}


static void ProtocolConfirmOneParameterUnpack( char *_parameter1, char *_packet)
{
    strcpy((char*)_parameter1, _packet+2);
}


static size_t ProtocolConfirmThreeParameterPack(char *_parameter1,char *_parameter2, char *_parameter3, char *_packet)
{
    char lenparameter1, lenparameter2, lenparameter3;
    lenparameter1 = (char)(strlen(_parameter1)+1);
    lenparameter2 = (char)(strlen(_parameter2)+1);
    lenparameter3 = (char)(strlen(_parameter3)+1);
    _packet[1]=lenparameter1;
    strcpy(_packet+2, _parameter1);
    _packet[2+lenparameter1]=lenparameter2;
    strcpy(_packet+3+lenparameter1, _parameter2);
    _packet[3+lenparameter1+lenparameter2]=lenparameter3;
    strcpy(_packet+4+lenparameter1+lenparameter2, _parameter3);
    return (lenparameter1+lenparameter2+lenparameter3+4);
}

static void ProtocolConfirmThreeParameterUnpack(char *_parameter1,char *_parameter2, char *_parameter3, char *_packet)
{
    int lenparameter1, lenparameter2, lenparameter3;
    lenparameter1 = (int)_packet[1];
    strcpy((char*)_parameter1, _packet+2);
    _parameter1[lenparameter1]='\0';
    lenparameter2 =(int)_packet[2+lenparameter1];
    strcpy((char*)_parameter2, _packet+3+lenparameter1);
    _parameter2[lenparameter2]='\0';
    lenparameter3=(int)_packet[3+lenparameter1+lenparameter2];
    strcpy(_parameter3, _packet+4+lenparameter1+lenparameter2);
    _parameter3[lenparameter3]='\0';

}


static void ProtocolOneParametersUnpack(char *_parameter1, char *_packet)
{
    int lenParameter1 = (int)_packet[1];
    strcpy((char*)_parameter1 ,_packet + 2);
    _parameter1[lenParameter1]='\0';
}
