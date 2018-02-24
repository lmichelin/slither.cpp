CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -O3
EXEC_NAME = main
INCLUDES = -Iheaders
LIBS = -IC:\C++\SFML-2.4.2\include -LC:\C++\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lpthread
SRC_DIR = src
OBJ_DIR = objs
INSTALL_DIR = build


SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OTMP = $(patsubst %.cpp,%.o,$(SRC_FILES:$(SRC_DIR)/%=%))
OBJ_FILES = $(patsubst %,$(OBJ_DIR)/%,$(OTMP))

all : init $(EXEC_NAME)

init: 
	@echo Initializing...
	mkdir -p $(OBJ_DIR)

clean :
	@echo Clearing...
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -o $@ -c $<

install :
	mv $(EXEC_NAME) $(INSTALL_DIR)