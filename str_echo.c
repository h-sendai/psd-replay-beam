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

int print_array_in_hex(unsigned char *buf, int len)
{
	int i;
	for (i = 0; i < len; i ++) {
		fprintf(stderr, "%x", buf[i]);
		if (i != len - 1) {
			fprintf(stderr, " ");
		}
	}
	fprintf(stderr, "\n");
	return 0;
}

int prepare_return_data(int filefd, char *buf, unsigned int len)
{
	static int file_eof = 0;
	int n;
	if (len > BUF_SIZE) {
		errx(1, "length too large: %d", len);
	}
	if (! file_eof) {
		n = read(filefd, buf, len);
		if (n < 0) {
			err(1, "data file read error");
		}
		if (n == 0) {
			file_eof = 0;
		}
	}
	else {
		n = 0;
	}
	return n;

	/* XXX: event data and t0 data.  Must exclude t0 data from data length? */
	/*
	 * for (i = 0; i < requested_length; i = i + 8) {
	 *	if (buf[i] != 0x5a) {
	 *		return_length --;
	 *	}
	 * }
	 */
}

int str_echo(int sockfd, char *filename)
{
	unsigned char	request_buf[LENGTH_REQUEST];
	unsigned char	buf[BUF_SIZE];
	unsigned int	requested_length;
	int				m;
	int				filefd;
	unsigned int	return_length;
	unsigned int	return_length_in_word;
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
			print_array_in_hex(request_buf, LENGTH_REQUEST);
		}

		requested_length = 
			(request_buf[4] << 24) +
			(request_buf[5] << 16) +
			(request_buf[6] <<  8) +
			(request_buf[7]      );
		requested_length = requested_length * 2;

		if (dflag) {
			fprintf(stderr, "length: %u\n", requested_length);
		}

		if (requested_length > BUF_SIZE) {
			errx(1, "requested length too large: %d", requested_length);
		}

		return_length = prepare_return_data(filefd, buf, requested_length);
		return_length_in_word = htonl(return_length/2); /* in words */

		if (dflag) {
			fprintf(stderr, "return_length_in_word: %u\n", return_length/2);
		}
		iov[0].iov_base = &return_length_in_word;
		iov[0].iov_len  = sizeof(return_length_in_word);
		iov[1].iov_base = buf;
		iov[1].iov_len  = return_length;
		if (sflag) {
			usleep(usleep_time);
		}
		if (writev(sockfd, iov, 2) != sizeof(return_length_in_word) + return_length) {
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
