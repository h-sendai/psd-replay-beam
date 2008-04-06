#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "my_signal.h"

#define SERV_PORT		23456
#define LISTENQ			10
#define SA				struct sockaddr

int dflag       = 0;
int sflag       = 0;
int usleep_time = 0;

extern int str_echo(int, char *);

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		;
	}
	return;
}

void usage(void)
{
	fprintf(stderr, "psd_replay [-d] [-h ip_address] [-p port] [-s usleep] file\n");
	return;
}

int main(int argc, char *argv[])
{
	char               *filename;
	char			   *ip_address;
	int					ch;
	int					filefd;
	int					listenfd, connfd;
	int					port;
	int					on = 1;
	int					hflag = 0;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	port = SERV_PORT;
	while( (ch = getopt(argc, argv, "dh:p:s:")) != -1) {
		switch(ch) {
			case 'd':
				dflag = 1;
				break;
			case 'h':
				hflag = 1;
				ip_address = optarg;
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 's':
				sflag = 1;
				usleep_time = atoi(optarg);
				break;
			case '?':
			default:
				break;
		}
	}
	
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		usage();
		exit(1);
	}

	filename = argv[0];
	if ( (filefd = open(filename, O_RDONLY)) < 0) {
		err(1, "cannot read file: %s", filename);
	}
	close(filefd);
	if (hflag) {
		if (inet_addr(ip_address) == INADDR_NONE) {
			errx(1, "invalid IP address");
		}
	}

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err(1, "socket");
	}
	setsockopt(listenfd, SOL_SOCKET,  SO_REUSEADDR, &on, sizeof(on));
	/* XXX */
	/* setsockopt(listenfd, IPPROTO_TCP, TCP_NODELAY , &on, sizeof(on)); */

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(port);
	if (hflag) {
		servaddr.sin_addr.s_addr = inet_addr(ip_address);
	}
	else {
		servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}

	if (bind(listenfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
		err(1, "bind");
	}

	if (listen(listenfd, LISTENQ) < 0) {
		err(1, "listen");
	}
	
	my_signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
				err(1, "accept");
			}
		}

		if ( (childpid = fork()) < 0) {
			err(1, "fork");
		}

		if (childpid == 0) { /* child */
			close(listenfd);
			str_echo(connfd, filename);
			exit(0);
		}
		else { /* parent */
			close(connfd);
		}
	}
}
