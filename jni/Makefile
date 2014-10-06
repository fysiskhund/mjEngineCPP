# Based on answer provided by http://stackoverflow.com/a/2484343

CC	   := g++
LD	   := g++

MODULES   := game gnuLinux core entities extLibs graphics physics terrainTypes extLibs/logger extLibs/math extLibs/png/include  extLibs/tinyxml
SRC_DIR   := $(addprefix ./,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

SRC	  := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
OBJ	  := $(patsubst ./%.cpp,build/%.o,$(SRC))
INCLUDES  := $(addprefix -I,$(SRC_DIR))

CFLAGS	  := -DDESKTOP_SDL -g -std=c++11 -lSDL2 -lpng16 -lGLESv2 -lSDL2_image

vpath %.cpp $(SRC_DIR)

define make-goal
$1/%.o: %.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c $$< -o $$@
endef

.PHONY: all checkdirs clean

all: checkdirs build/mjEngine.out

build/mjEngine.out: $(OBJ)
	$(LD) $(CFLAGS) $^ -o $@


checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(BUILD_DIR)

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))
