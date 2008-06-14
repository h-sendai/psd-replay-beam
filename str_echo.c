#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "psd_replay.h"

#define LENGTH_REQUEST	8
#define REQUEST_HEADER	0xa3
#define BUF_SIZE        2 * 1024 * 1024

int word2byte(int word)
{
	return word * 2;
}

int byte2word(int byte)
{
	return byte / 2;
}

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

/* 
 * NEUNET Protocol note
 * Return length of the data contains event data, t0 data, etc.
 * For example, if we have 100 event data and 2 t0 data, we will
 * return a value (100 + 2) * 4 = 408 as the data length.
 */

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
			/* XXX -F flag: Forever mode */
			if (Fflag) {
				lseek(filefd, 0, SEEK_SET);
				n = read(filefd, buf, len);
				if (n < 0) {
					err(1, "data file read error");
				}
			}
			else {
				file_eof = 0;
				if (vflag) {
					fprintf(stderr, "NO MORE DATA and I DO NOT RE-READ IT!\n");
				}
			}
		}
	}
	else {
		n = 0;
	}
	return n;
}

int str_echo(int sockfd, char *filename)
{
	unsigned char	request_buf[LENGTH_REQUEST];
	unsigned char	buf[BUF_SIZE];
	unsigned int	requested_word_length = 0;
	unsigned int	requested_byte_length = 0;
	int				m;
	int				filefd;
	unsigned int	return_length = 0;
	unsigned int	return_length_in_word = 0;
	struct iovec	iov[2];
	double			ualarm_interval;
	static int		remain_data_byte_size = 0;

    if ( (filefd = open(filename, O_RDONLY)) < 0) {
		err(1, "open");
	}

	if (Hflag) {
		ualarm_interval = 1000000 / Hz;
	}
	else {
		ualarm_interval = 1000000 / 25;
	}

	ualarm(ualarm_interval, ualarm_interval);

READ_AGAIN:
	while ( (m = recv(sockfd, request_buf, sizeof(request_buf), MSG_WAITALL)) > 0) {
		if (request_buf[0] != REQUEST_HEADER) {
			errx(1, "invalid request header");
		}
		if (dflag) {
			print_array_in_hex(request_buf, LENGTH_REQUEST);
		}

		requested_word_length = 
			(request_buf[4] << 24) +
			(request_buf[5] << 16) +
			(request_buf[6] <<  8) +
			(request_buf[7]      );
		requested_byte_length = word2byte(requested_word_length);

		if (dflag) {
			fprintf(stderr, "length: %u\n", requested_byte_length);
		}

		if (requested_byte_length > BUF_SIZE) {
			errx(1, "requested length too large: %d", requested_byte_length);
		}
		
		if (event_flag == 1) {
			event_flag = 0;
			remain_data_byte_size = data_byte_size_per_shot;
		}

		if (remain_data_byte_size > 0) {
			int try_read_len;
			if (remain_data_byte_size > requested_byte_length) {
				try_read_len = requested_byte_length;
				//remain_data_byte_size -= try_read_len;
			}
			else {
				try_read_len = remain_data_byte_size;
				//remain_data_byte_size = 0;
			}
			return_length = prepare_return_data(filefd, buf,
								try_read_len);
			remain_data_byte_size -= return_length;
			return_length_in_word = htonl(byte2word(return_length));
			/* in words */
		}
		else {
			return_length = 0;
			return_length_in_word = 0;
		}

		iov[0].iov_base = &return_length_in_word;
		iov[0].iov_len  = sizeof(return_length_in_word);
		iov[1].iov_base = buf;
		iov[1].iov_len  = return_length;
		if (sflag) {
			usleep(usleep_time);
		}
		//if (writev(sockfd, iov, 2) != sizeof(return_length_in_word) + return_length) {
		if (writev(sockfd, iov, 2) == -1) {
			int pid = getpid();
			err(1, "pid: %d: writev", pid);
		}
	}
	if (m < 0) { 
		if (errno == EINTR) {
			goto READ_AGAIN;
		}
		else {
			err(1, "(client exit?)");
		}
	}
	if (dflag) { /* m == 0 */
		fprintf(stderr, "child exit\n");
	}
	return 0;
}
