
COMPILER = g++

FLAGS = \
 -Wno-unused-parameter -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal 						\
 -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-default -Weffc++ -Wmain 			\
 -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wctor-dtor-privacy -Wempty-body -Wformat-security 					\
 -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual 		\
 -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -ggdb3 -Wtype-limits -Wwrite-strings \

OBJ_DIR = ./obj
SRC_DIR = ./src

PLUGIN_DIR = Plugins

BIN = run

INC_FLAGS = -I$(SRC_DIR)


DLL = $(shell find $(SRC_DIR)/$(PLUGIN_DIR) -type f -name "*.cpp")

CPP := $(shell find $(SRC_DIR) -type f -name "*.cpp")
CPP := $(filter-out $(DLL), $(CPP))

OBJ = $(CPP:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DLL_OBJ = $(DLL:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

DLL_SO = $(DLL:$(SRC_DIR)/%.cpp=%.so)


DEP = $(OBJ:%.o=%.d)

all : build plugins
	@./$(BIN)


.PHONY : build
build : $(BIN)

$(BIN) : $(OBJ) $(DLL_OBJ)
	@mkdir -p $(@D)
	@$(COMPILER) $(OBJ) -o $(BIN) -lsfml-graphics -lsfml-window -lsfml-system

.PHONY : plugins
plugins : $(DLL_SO)

-include $(DEP)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(COMPILER) $(FLAGS) $(INC_FLAGS) -MMD -fPIC -c $< -o $@

$(PLUGIN_DIR)/%.so : $(OBJ_DIR)/$(PLUGIN_DIR)/%.o obj/Impl/LayoutBox/BaseLayoutBox/BaseLayoutBox.o obj/Impl/Widget/Widget.o obj/Impl/Graphic/Graphic.o obj/Impl/Widget/Window/Window.o obj/Impl/Widget/ContainerWidget/ContainerWidget.o obj/Impl/Widget/Button/Button.o 	\
	@mkdir -p $(@D)
	@$(COMPILER) -shared -z defs -o $@ $^

.PHONY : cleanup
cleanup :
	@rm -rf $(BIN) $(OBJ_DIR)