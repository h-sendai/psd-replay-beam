#ifndef _PSD_REPLY_H
#define _PSD_REPLY_H 1

/*
#define SERV_PORT       23456
#define LISTENQ         10
#define SA              struct sockaddr
*/

#define MAX_HZ 30

#include <signal.h>

extern int dflag;
extern int Hflag;
extern int sflag;
extern int Fflag;
extern int vflag;

extern int Hz;
extern int usleep_time;
extern volatile sig_atomic_t event_flag;
extern int data_byte_size_per_shot;

extern int str_echo(int, char *);

#endif
