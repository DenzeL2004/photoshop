all: mkdirectory run

FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 		\
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion	\
		-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers		\
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel  	\
		-Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE


SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


run:		obj/vector.o obj/graphic.o obj/window.o obj/log_errors.o obj/generals.o obj/main.o
	g++   	obj/vector.o obj/graphic.o obj/window.o obj/log_errors.o obj/generals.o obj/main.o -o run  $(SFML_FLAGS)


obj/main.o: main.cpp
		g++ main.cpp -c -o obj/main.o $(FLAGS)



obj/log_errors.o: src/log_info/log_errors.h src/log_info/log_errors.cpp
			g++   src/log_info/log_errors.cpp -c -o obj/log_errors.o $(FLAGS)

obj/generals.o: src/generals_func/generals.cpp src/generals_func/generals.h
			g++ src/generals_func/generals.cpp -c -o obj/generals.o $(FLAGS)


obj/vector.o: src/vector/vector.cpp src/vector/vector.h
		g++   src/vector/vector.cpp -c -o obj/vector.o $(FLAGS)


obj/graphic.o: src/graphic/graphic.cpp src/graphic/graphic.h src/graphic/graphic_config.h
		g++    src/graphic/graphic.cpp -c -o obj/graphic.o $(FLAGS) $(SFML_FLAGS)

obj/window.o:  	src/widget/window/window.cpp src/widget/window/window.h
		g++		src/widget/window/window.cpp -c -o obj/window.o $(FLAGS)

.PHONY: cleanup mkdirectory

mkdirectory:
	mkdir -p obj;
	mkdir -p tmp;
	

cleanup:
	rm obj/*.o