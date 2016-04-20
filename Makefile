cc = clang
objs = main.o Shader.o Texture.o ViewVolume.o Shadow.o Vec2.o Vec3.o Face.o Object.o Scenery.o
flags = -g -L/usr/lib64 -lX11 -lGL -lGLU -lglut -lm

all: $(objs)
	$(cc) -o render $(objs) $(flags)

main.o : main.c
	$(cc) -c main.c $(flags)
clean:
	rm render $(objs)
