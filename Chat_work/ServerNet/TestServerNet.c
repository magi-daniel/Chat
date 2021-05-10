#include "../mu_test.h"
#include "ServerNet.h"
#include <stdint.h>

static ServerNetErr PingPong(void* _recieved, size_t _size, int _sock, void* _context)
{
    static size_t i;
    if(i == 10000)
    {
        i = 0;
        return SERVER_NET_STOP;
    }
    if(_size == 0 || _context == NULL)
    {}
    ++i;
    printf("%s\n", (char*)_recieved);
    return ServerNetSend(_sock, "Pong", 5);
}

static ServerNetErr FailCheck(ServerNetErr _status, int _errno, void* _context)
{
    if(_status || _errno || _context)
    {}
    return SERVER_NET_STOP;
}

static void Accept(int _sock, void* _context)
{
    if(_context)
    {}
    printf("Hi %d\n", _sock);
}

UNIT(create_server_works)
    ServerNet *serverNet;

    ASSERT_THAT((serverNet = ServerNetCreate(100, 1080, 100, PingPong, NULL, NULL, NULL, NULL)) != NULL);
    ServerNetDestroy(&serverNet);
    ASSERT_THAT((serverNet = ServerNetCreate(100, 1081, 100, PingPong, NULL, Accept, Accept, NULL)) != NULL);
    ServerNetDestroy(&serverNet);
    ASSERT_THAT((serverNet = ServerNetCreate(100, 1082, 100, PingPong, FailCheck, Accept, Accept, NULL)) != NULL);
    ServerNetDestroy(&serverNet);
    ASSERT_THAT(serverNet == NULL);
END_UNIT

UNIT(check_server_with_invalid_parameters)
    ASSERT_THAT(ServerNetCreate(100, 1055, 100, NULL, NULL, NULL, NULL, NULL) == NULL);
    ASSERT_THAT(ServerNetCreate(-5, 1055, 100, PingPong, NULL, NULL, NULL, NULL) == NULL);
    ASSERT_THAT(ServerNetCreate(100, 1000, 100, PingPong, NULL, NULL, NULL, NULL) == NULL);
    ASSERT_THAT(ServerNetCreate(100, 1055, 100, PingPong, NULL, NULL, Accept, NULL) == NULL);
    ASSERT_THAT(ServerNetCreate(100, 1055, 100, PingPong, NULL, Accept, NULL, NULL) == NULL);
END_UNIT
/*
UNIT(check_run_works_with_singel_client)
    ServerNet* ServerNet;

    ASSERT_THAT((ServerNet = ServerNetCreate(100, 1234, 100, PingPong, FailCheck, NULL, NULL, NULL)) != NULL);
    ServerNetRun(ServerNet);
    ServerNetDestroy(&ServerNet);
    ASSERT_THAT(ServerNet == NULL);
END_UNIT
*/
UNIT(check_run_works)
    ServerNet* ServerNet;

    ASSERT_THAT((ServerNet = ServerNetCreate(100, 1055, 100, PingPong, FailCheck, NULL, NULL, NULL)) != NULL);
    ServerNetRun(ServerNet);
    ServerNetDestroy(&ServerNet);
    ASSERT_THAT(ServerNet == NULL);
END_UNIT

UNIT(check_run_when_null)
    ASSERT_THAT(ServerNetRun(NULL) == SERVER_NET_NOT_INITIALIZED);
END_UNIT

UNIT(check_send_when_invalid_parameters)
    int i = 5;
    
    ASSERT_THAT(ServerNetSend(-30, &i, 4) == SERVER_NET_SEND_PARAMETERS_ERROR);
    ASSERT_THAT(ServerNetSend(20, NULL, 4) == SERVER_NET_SEND_PARAMETERS_ERROR);
    ASSERT_THAT(ServerNetSend(20, &i, 0) == SERVER_NET_SEND_PARAMETERS_ERROR);
END_UNIT

UNIT(check_send_when_socket_closed)
    int i = 5;

    ASSERT_THAT(ServerNetSend(29, &i, 4) == SERVER_NET_SEND_ERROR);
END_UNIT

TEST_SUITE(ServerNet)
    TEST(create_server_works)
    TEST(check_server_with_invalid_parameters)
   /* TEST(check_run_works_with_singel_client)*/
    TEST(check_run_works)
    TEST(check_run_when_null)
    TEST(check_send_when_invalid_parameters)
    TEST(check_send_when_socket_closed)
END_SUITE