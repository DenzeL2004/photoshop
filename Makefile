all: mkdirectory run

FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations 		\
		-Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion	\
		-Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers		\
		-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel  	\
		-Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE


SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


run:		obj/log_errors.o obj/generals.o obj/vector.o obj/graphic.o obj/event.o obj/transform.o obj/layout.o obj/widget.o 			\
			obj/window.o obj/button.o obj/decorator.o obj/canvas.o obj/filter.o obj/tools.o obj/app.o obj/color_palette.o obj/text_box.o obj/main.o

	g++   	obj/log_errors.o obj/generals.o obj/vector.o obj/graphic.o obj/event.o obj/transform.o obj/layout.o obj/widget.o 			\
		 	obj/window.o obj/button.o obj/decorator.o obj/canvas.o obj/filter.o obj/tools.o obj/app.o obj/color_palette.o obj/text_box.o obj/main.o -o run  $(SFML_FLAGS)


obj/main.o: main.cpp
		g++ main.cpp -c -o obj/main.o $(FLAGS)



obj/log_errors.o: 	src/log_info/log_errors.h src/log_info/log_errors.cpp
		g++   		src/log_info/log_errors.cpp -c -o obj/log_errors.o $(FLAGS)

obj/generals.o: src/generals_func/generals.cpp src/generals_func/generals.h
		g++ 	src/generals_func/generals.cpp -c -o obj/generals.o $(FLAGS)


obj/vector.o: 	src/vector/vector.cpp src/vector/vector.h
		g++   	src/vector/vector.cpp -c -o obj/vector.o $(FLAGS)


obj/graphic.o: 	src/graphic/graphic.cpp src/graphic/graphic.h src/graphic/graphic_config.h
		g++    	src/graphic/graphic.cpp -c -o obj/graphic.o $(FLAGS) $(SFML_FLAGS)




obj/app.o:  	src/app/app.cpp src/app/app.h
		g++		src/app/app.cpp -c -o obj/app.o $(FLAGS)




obj/event.o:  	src/widgets/event/event.cpp src/widgets/event/event.h
		g++		src/widgets/event/event.cpp -c -o obj/event.o $(FLAGS)

obj/layout.o:	src/widgets/widget/layoutbox/layoutbox.cpp src/widgets/widget/layoutbox/layoutbox.h
		g++ 	src/widgets/widget/layoutbox/layoutbox.cpp -c -o obj/layout.o $(FLAGS)

obj/transform.o: 	src/widgets/widget/transform/transform.cpp src/widgets/widget/transform/transform.h
		g++    		src/widgets/widget/transform/transform.cpp -c -o obj/transform.o $(FLAGS)

obj/widget.o:  	src/widgets/widget/widget.cpp src/widgets/widget/widget.h
		g++		src/widgets/widget/widget.cpp -c -o obj/widget.o $(FLAGS)

obj/window.o:  	src/widgets/window/window.cpp src/widgets/window/window.h
		g++		src/widgets/window/window.cpp -c -o obj/window.o $(FLAGS)

obj/button.o:  	src/widgets/button/button.cpp src/widgets/button/button.h
		g++		src/widgets/button/button.cpp -c -o obj/button.o $(FLAGS)

obj/decorator.o:  	src/widgets/decorator/decorator.cpp src/widgets/decorator/decorator.h
		g++			src/widgets/decorator/decorator.cpp -c -o obj/decorator.o $(FLAGS)


obj/canvas.o:  	src/widgets/window/canvas.cpp src/widgets/window/canvas.h
		g++		src/widgets/window/canvas.cpp -c -o obj/canvas.o $(FLAGS)


obj/tools.o:  	src/widgets/window/tools/tools.cpp src/widgets/window/tools/tools.h
		g++		src/widgets/window/tools/tools.cpp -c -o obj/tools.o $(FLAGS)

obj/filter.o:  	src/widgets/window/filters/filter.cpp src/widgets/window/filters/filter.h
		g++		src/widgets/window/filters/filter.cpp -c -o obj/filter.o $(FLAGS)

obj/color_palette.o:  	src/widgets/window/color_palette/color_palette.cpp src/widgets/window/color_palette/color_palatte.h
		g++				src/widgets/window/color_palette/color_palette.cpp -c -o obj/color_palette.o $(FLAGS)

obj/text_box.o:	src/widgets/text_box/text_box.cpp src/widgets/text_box/text_box.h
		g++				src/widgets/text_box/text_box.cpp -c -o obj/text_box.o $(FLAGS)

.PHONY: cleanup mkdirectory

mkdirectory:
	mkdir -p obj;
	mkdir -p tmp;
	

cleanup:
	rm obj/*.o