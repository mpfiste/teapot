cc = clang
objs = main.o
flags = -g -L/usr/lib64 -lX11 -lGL -lGLU -lglut -lm

all: $(objs)
	$(cc) -o render $(objs) $(flags)

main.o : main.c
	$(cc) -c main.c $(flags)
clean:
	rm render $(objs)
