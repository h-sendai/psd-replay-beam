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
#include "psd_replay.h"

#define SERV_PORT		23456
#define NEUNET_PORT		23
#define LISTENQ			10
#define SA				struct sockaddr

int cflag = 0;
int dflag = 0;
int Hflag = 0;
int sflag = 0;
int Sflag = 0;
int Fflag = 0;
int vflag = 0;
int zflag = 0;
int Pflag = 0;
int Hz = 0;

int return_data_counter = 0;
int usleep_time = 0;
int data_send_probability = 0;
int return_data_size = 0;

volatile sig_atomic_t event_flag = 1;
int data_byte_size_per_shot = 100000; /* default event data byte size */

void sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		;
	}
	return;
}

void sig_alarm(int signo)
{
	event_flag = 1;
	return;
}

void usage(void)
{
	char *usage_message =
"usage: psd_replay_beam [-d] [-H hz] [-F] [-h ip_address] [-n data_size] [-p port] [-s usleep] [-v] data_file\n"
"Options:\n"
"    -d            debug\n"
"    -H hz         beam Hz (1 - 30)\n"
"    -F            forever mode.  Read data file again when reach EOF.\n"
"    -h ip_address listen IP address\n"
"    -n data_size  data bytes size per one beam shot\n"
"    -s usleep     sleep usleep usec just before sending data\n"
"    -v            verbose\n";

	fprintf(stderr, usage_message);
	return;
}

void print_priv_port_notice(int port)
{
	char *message;
	message = "You need root privilege to use port %d.\n"
			  "Use -p option to change listening port.\n";
	fprintf(stderr, message, port);
	return;
}
  
void print_caution_on_port(int port)
{
	char *message;
	message = "\n"
"NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE\n"
"\n"
"           DANGER, Will Robinson! DANGAR! DANGER!\n"
"\n"
"You are trying to listen on port %d.\n"
"This is not a default port of the NEUNET module.\n"
"The Gatherer component may not be able to connect this port.\n"
"Use -p option to specify the listening port number.\n"
"If you use port 23 (NEUNET default port), you have to become\n"
"root user to listen on port 23.\n"
"\n"
"NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE\n"
"\n";
	fprintf(stderr, message, port);
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
	while( (ch = getopt(argc, argv, "dFh:H:n:p:s:v")) != -1) {
		switch(ch) {
			case 'd':
				dflag = 1;
				break;
			case 'F':
				Fflag = 1;
				break;
			case 'h':
				hflag = 1;
				ip_address = optarg;
				break;
			case 'H':
				Hflag = 1;
				Hz = atoi(optarg);
				if (Hz <= 0 || Hz > MAX_HZ) {
					usage();
					exit(1);
				}
				break;
			case 'n':
				data_byte_size_per_shot = atoi(optarg);
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 's':
				sflag = 1;
				usleep_time = atoi(optarg);
				break;
			case 'v':
				vflag = 1;
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
	
	if (port != NEUNET_PORT) {
		print_caution_on_port(port);
	}

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
		int uid = getuid();
		if ( (errno == EACCES) && (port < 1024) && (uid != 0)) {
			print_priv_port_notice(port);
			exit(1);
		}
		else {
			err(1, "bind");
		}
	}

	if (listen(listenfd, LISTENQ) < 0) {
		err(1, "listen");
	}
	
	my_signal(SIGCHLD, sig_chld);
	my_signal(SIGALRM, sig_alarm);

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
