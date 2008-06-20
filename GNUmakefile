PROG = psd_replay_beam

CFLAGS = -g -O0 -Wall -D_FILE_OFFSET_BITS=64

OBJS += psd_replay.o
OBJS += my_signal.o
OBJS += str_echo.o
OBJS += may_send.o

all: ${PROG}

${PROG}: ${OBJS}
	cc -o ${PROG} ${OBJS}

my_signal.o:  my_signal.h
psd_replay.o: psd_replay.h
str_echo.o:   psd_replay.h

clean:
	rm -f ${OBJS} ${PROG}
