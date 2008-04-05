CFLAGS = -g -O0 -Wall
PROG = psd_replay

SRCS += psd_replay.c

NO_MAN = true
NO_OBJ = true

.include <bsd.prog.mk>
