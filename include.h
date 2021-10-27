#include <stdio.h>
#include <glib.h>
#include <gio/gio.h>
#include <unistd.h>		/* For sleep() */
#include <string.h>		/* For strlen() */
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>
#include <arpa/inet.h>
#define PORT 23456