lifesim: main.c reader.c simulate.c next_gen.c txt_writer.c png_writer.c
	gcc main.c reader.c simulate.c next_gen.c txt_writer.c png_writer.c -lpng -o lifesim
