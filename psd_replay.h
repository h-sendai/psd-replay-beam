#ifndef _PSD_REPLY_H
#define _PSD_REPLY_H 1

/*
#define SERV_PORT       23456
#define LISTENQ         10
#define SA              struct sockaddr
*/

extern int dflag;
extern int sflag;
extern int Fflag;
extern int vflag;
extern int zflag;
extern int Pflag;
extern int usleep_time;
extern int data_send_probability;

extern int str_echo(int, char *);
extern int may_send(void);

#endif
