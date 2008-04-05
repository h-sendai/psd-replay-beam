#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define SERV_PORT 23456
#define ONE_EVENT 8
#define LENGTH_REQUEST 8
#define REQUEST_HEADER 0xa3
#define LISTENQ   10

int str_echo(int sockfd, char *filename)
{
	unsigned char request_buf[LENGTH_REQUEST];
	char buf[2 * 1024 * 1024];
	int requested_length;
	int i, m, n;
	int filefd;
	int length_return;
	int file_eof = 0;
	struct iovec iov[2];

	if ( (filefd = open(filename, O_RDONLY)) < 0) {
		err(1, "open");
	}

	while ( (m = recv(sockfd, request_buf, sizeof(request_buf), MSG_WAITALL)) > 0) {
		fprintf(stderr, "while exit\n");
		if (request_buf[0] != REQUEST_HEADER) {
			warn("invalid request header");
			return -1;
		}
		fprintf(
			stderr,
			"request_buf: %x %x %x %x %x %x %x %x\n",
			request_buf[0],
			request_buf[1],
			request_buf[2],
			request_buf[3],
			request_buf[4],
			request_buf[5],
			request_buf[6],
			request_buf[7]
		);
		fprintf(stderr, "length calculate\n");
		requested_length = 
			( request_buf[4] << 24 ) +
			( request_buf[5] << 16 ) +
			( request_buf[6] <<  8 ) +
			( request_buf[7]       );
		requested_length = requested_length * 4;
		fprintf(stderr, "length: %d\n", requested_length);
		if (requested_length > 2 * 1024 * 1024) {
			err(1, "length too large");
		}
		if (file_eof != 1) {
			n = read(filefd, buf, requested_length);
			if (n < 0) {
				err(1, "read");
			}
			if (n == 0) {
				file_eof = 1;
			}
			length_return = n;
			//for (i = 0; i < requested_length; i = i + 8) {
			//	if (buf[i] != 0x5a) {
			//		length_return --;
			//	}
			//}
			length_return = htonl(length_return/2);
			iov[0].iov_base = &length_return;
			iov[0].iov_len  = sizeof(length_return);
			iov[1].iov_base = buf;
			iov[1].iov_len  = n;

			if (writev(sockfd, &iov[0], 2) != n + sizeof(length_return)) {
				err(1, "length + data write");
			}
		}
		else {
			/* XXX: same codes appear twice */
			length_return = 0;
			if (write(sockfd, &length_return, sizeof(length_return)) != sizeof(length_return)) {
				err(1, "length return write (with length 0)");
			}
		}
	}
	if (m < 0) { 
		err(1, "recv length request");
	}
	fprintf(stderr, "return to main\n");
	return 0;
}

void usage(void)
{
	fprintf(stderr, "psd_replay [-p port] file\n");
	return;
}

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	int					on = 1;
	char               *filename;
	int					ch;
	int					port;
	int					filefd;

	port = SERV_PORT;
	while( (ch = getopt(argc, argv, "p:")) != -1) {
		switch(ch) {
			case 'p':
				port = atoi(optarg);
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

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err(1, "socket");
	}
	setsockopt(listenfd, SOL_SOCKET,  SO_REUSEADDR, &on, sizeof(on));
	/* XXX */
	/* setsockopt(listenfd, IPPROTO_TCP, TCP_NODELAY , &on, sizeof(on)); */

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(port);

	if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		err(1, "bind");
	}

	if (listen(listenfd, LISTENQ) < 0) {
		err(1, "listen");
	}

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
			err(1, "accept");
		}
		str_echo(connfd, filename);
		close(connfd);
	}
}
