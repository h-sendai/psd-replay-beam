CFLAGS = -g -O0 -Wall
PROG = psd_replay

SRCS += psd_replay.c
SRCS += my_signal.h
SRCS += my_signal.c
SRCS += str_echo.c

NO_MAN = true
NO_OBJ = true

.include <bsd.prog.mk>
