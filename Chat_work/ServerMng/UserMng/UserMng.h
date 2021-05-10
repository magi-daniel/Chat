#ifndef __USERMNG_H__
#define __USERMNG_H__
#include "../../DS/libH/HashMap.h"
#include "../../DS/libH/list.h"

typedef struct UserMng UserMng;


typedef enum UserMngResult 
{
    USERMNG_OK,
    USERMNG_DUPLICATE_ERR,
    USERMNG_NULL_PARAMETER_ERR, 
    USERMNG_HASH_ERR,
    USERMNG_ALLOCATION_FAILED,
    USERMNG_ALREADY_ONLINE,
    USERMNG_LOGIN_SUCCEDDFULLY,
    USERMNG_LIST_ERR,
    USERMNG_WRONG_PASSWORD,
    USERMNG_GROUP_NOT_FOUND
} UserMngResult;


typedef enum
{
    ONLINE,
    OFFLINE
} Status;



/*
Description: user mng get hash map.
Input: get user mng.
Output: return user mng hash map.
Error: if parameter not good return NULL.
*/
HashMap* UserMngGetHash(UserMng *_userMng);

/*
Description: get the status the user
Input: get user
Output: return the status the user
Error: NONE.
*/
Status UserMngGetStatus(void *_user);

/*
Description: user mng create.
Input:NONE.
Output: return user mng
Error: if malloc failed return NULL.
if hash map create return NULL
*/
UserMng* UserMngCreate();
/*
Description: user mng registration
Input: get user mng, user name and password
Output: return USERMNG_OK.
Error:if parameter not good return USERMNG_NULL_PARAMETER_ERR.
if have this user in system return USERMNG_DUPLICATE_ERR.
if user create failed return USERMNG_ALLOCATION_FAILED.
if insert the user to system return USERMNG_HASH_ERR.
*/
UserMngResult UserMngRegistration(UserMng *_userMng,  char *_userName, char* _password);

/*
Description: user login
Input: get user mng, user name, password.
Output:return USERMNG_LOGIN_SUCCEDDFULLY.
Error: if parameter not good return USERMNG_NULL_PARAMETER_ERR.
if hashmap find failed return USERMNG_HASH_ERR.
if the user already online return USERMNG_ALREADY_ONLINE.
if password not good USERMNG_WRONG_PASSWORD
*/
UserMngResult UserMngLogin(UserMng *_userMng,  char *_userName, char* _password);

/*
Description: join user mng to group.
Input: get user mng , user name, gorup name
Output: return USERMNG_OK.
Error: if parameter not good return USERMNG_NULL_PARAMETER_ERR.
if find the user name failed return USERMNG_HASH_ERR.
if malloc name failed return USERMNG_ALLOCATION_FAILED.
if add to list failed return USERMNG_LIST_ERR.
*/
UserMngResult UserMngJoinGroup(UserMng *_userMng,  char *_userName, char *_groupName);

/*
userMngLeaveGroup
Description: remove user from group.
Input:  _userMng - pointer to the userMng
        _userName - the name of the user to remove.
        _groupName - the name of the group that the user waant to leave.
Output: return USERMNG_OK.
Error: if parameter not good return USERMNG_NULL_PARAMETER_ERR.
if doesnt find the group in the hash retutn USERMNG_GROUP_NOT_FOUND
if there are problem in the hash - return USERMNG_HASH_ERR
*/
UserMngResult UserMngLeaveGroup(UserMng *_userMng,  char *_userName, char *_groupName);
/*
Description: change the status from online to offline
*/
void UserMngOfflineStatus(void *_user);

/*
Description: return list of specific cilent groups
*/
List* UserMngGetList(void *_user);



#endif /*__USERMNG_H__*/