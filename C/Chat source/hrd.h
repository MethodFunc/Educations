#ifndef __HRD_H__
#define __HRD_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>


#define IP_SERVER "192.168.0.4"
#define PORT_SERVER 10004
#define SIZE_BUF 256
#define MSG_END "break"

#endif	// __HRD_H__
