lifesim: main.o reader.o simulate.o next_gen.o generation.o gconfig.o png_writer.o txt_writer.o
	gcc main.o reader.o next_gen.o simulate.o generation.o gconfig.o png_writer.o txt_writer.o -lpng -o lifesim

main.o: main.c reader.o generation.o gconfig.o png_writer.o txt_writer.o simulate.o
	gcc -c -lpng main.c reader.c generation.c gconfig.c png_writer.c txt_writer.c simulate.c

reader.o: reader.c reader.h #generation.o
	gcc -c reader.c #generation.c

simulate.o: simulate.c simulate.h #generation.o gconfig.o next_gen.o 
	gcc -c simulate.c #generation.c gconfig.c next_gen.c

generation.o: generation.c generation.h
	gcc -c generation.c

gconfig.o: gconfig.c gconfig.h
	gcc -c gconfig.c

png_writer.o: png_writer.h png_writer.c #generation.o gconfig.o
	gcc -c -lpng png_writer.c #generation.c gconfig.c

txt_writer.o: txt_writer.h txt_writer.c #generation.o
	gcc -c txt_writer.c #generation.c 

clean:
	*.o
