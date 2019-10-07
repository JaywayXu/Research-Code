src:=$(wildcard *.c)
obj:=${src:%.c=%.o}
path=$(odir)

all:${obj}
%.o:%.c
	$(cc) -o ${odir}/$@ -c $< $(cflags)

