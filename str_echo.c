#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define LENGTH_REQUEST	8
#define REQUEST_HEADER	0xa3
#define BUF_SIZE        2 * 1024 * 1024

extern int dflag;
extern int sflag;
extern int usleep_time;

int str_echo(int sockfd, char *filename)
{
	unsigned char	request_buf[LENGTH_REQUEST];
	char			buf[BUF_SIZE];
	int				requested_length;
	int				m, n;
	int				filefd;
	int				length_return;
	int				file_eof = 0;
	struct iovec	iov[2];

	if ( (filefd = open(filename, O_RDONLY)) < 0) {
		err(1, "open");
	}

	while ( (m = recv(sockfd, request_buf, sizeof(request_buf), MSG_WAITALL)) > 0) {
		if (request_buf[0] != REQUEST_HEADER) {
			warn("invalid request header");
			return -1;
		}
		if (dflag) {
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
		}

		requested_length = 
			(request_buf[4] << 24) +
			(request_buf[5] << 16) +
			(request_buf[6] <<  8) +
			(request_buf[7]      );
		requested_length = requested_length * 4;

		if (dflag) {
			fprintf(stderr, "length: %d\n", requested_length);
		}

		if (requested_length > BUF_SIZE) {
			err(1, "requested length too large");
		}

		if (file_eof != 1) {
			n = read(filefd, buf, requested_length);
			if (n < 0) {
				err(1, "read");
			}
			if (n == 0) {
				file_eof = 1; /* for next request.  reduce read() overhead */
			}
			length_return = n;
			/*
			 * for (i = 0; i < requested_length; i = i + 8) {
			 *	if (buf[i] != 0x5a) {
			 *		length_return --;
			 *	}
			 * }
			 */
		}
		else {
			length_return = 0;
			n = 0;
		}

		length_return = htonl(length_return/2); /* return length in words */
		iov[0].iov_base = &length_return;
		iov[0].iov_len  = sizeof(length_return);
		iov[1].iov_base = buf;
		iov[1].iov_len  = n;
		if (sflag) {
			usleep(usleep_time);
		}
		if (writev(sockfd, &iov[0], 2) != n + sizeof(length_return)) {
			err(1, "length + data write");
		}
	}
	if (m < 0) { 
		err(1, "(client exit?)");
	}
	if (dflag) { /* m == 0 */
		fprintf(stderr, "child exit\n");
	}
	return 0;
}
