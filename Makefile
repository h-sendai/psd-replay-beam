CFLAGS = -g -O0 -Wall -D_FILE_OFFSET_BITS=64
PROG = psd_replay_beam

SRCS += psd_replay.c
SRCS += my_signal.h
SRCS += my_signal.c
SRCS += str_echo.c
SRCS += may_send.c

NO_MAN = true
NO_OBJ = true

.include <bsd.prog.mk>
