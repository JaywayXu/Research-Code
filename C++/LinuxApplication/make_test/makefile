dir:=$(shell pwd)
src:=$(wildcard *.c)
obj:=${src:%.c=%.o}
incpath:=-I$(dir)/functions -I./

export cflags+=$(incpath)
export cc=gcc
export odir=$(dir)

app=main
path=$(odir)

all:${app}
${app}:${obj} of
	$(cc) -o $@ ${odir}/*.o $(cflags)
%.o:%.c
	$(cc) -o ${odir}/$@ -c $< $(cflags)

of:
	@make -C functions/

