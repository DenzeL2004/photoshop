
COMPILER = g++


FLAGS = -Wno-unused-parameter -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal 						\
 		-Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Weffc++ -Wmain 				\
 		-Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wctor-dtor-privacy -Wempty-body -Wformat-security 						\
 		-Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual 		\
 		-Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings 	\


SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJ_DIR = ./obj
SRC_DIR = ./src

OUT_NAME = run


CPP = $(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJ = $(CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


INC_FLAGS = -I$(SRC_DIR)

DEP = $(OBJ:%.o=%.d)

all : makedir build
	./$(OUT_NAME)


build : $(OUT_NAME)

$(OUT_NAME) : $(OBJ)
	@mkdir -p $(@D)
	$(COMPILER) $^ -o $(OUT_NAME) $(SFML_FLAGS)


-include $(DEP)


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(COMPILER) $(FLAGS) $(INC_FLAGS) $(D_FLAGS) -MMD -c $< -o $@

.PHONY : makedir cleanup

makedir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p tmp;
	

cleanup :
	rm -rf $(OUT_NAME) $(OBJ_DIR)