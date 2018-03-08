CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES_SERVER = -Iserver/headers -Imixins/headers
INCLUDES_CLIENT = -Iclient/headers -Imixins/headers
INCLUDES_MIXINS = -Imixins/headers

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LIBS_SERVER = -lsfml-graphics -lsfml-system -lsfml-network -lpthread
	LIBS_CLIENT = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
	LIBS_CLIENT = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
endif
ifeq ($(UNAME), MSYS_NT-10.0)
	LIBS_SERVER = -IC:\C++\SFML-2.4.2\include -LC:\C++\SFML-2.4.2\lib -lsfml-graphics -lsfml-system -lsfml-network -lpthread
	LIBS_CLIENT = -IC:\C++\SFML-2.4.2\include -LC:\C++\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
	LIBS_MIXINS = -IC:\C++\SFML-2.4.2\include -LC:\C++\SFML-2.4.2\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
endif

SRC_CLIENT_DIR = client/src
SRC_SERVER_DIR = server/src
SRC_MIXINS_DIR = mixins/src
OBJ_CLIENT_DIR = client/objs
OBJ_SERVER_DIR = server/objs
OBJ_MIXINS_DIR = mixins/objs
INSTALL_DIR = build

SRC_CLIENT_FILES = $(wildcard $(SRC_CLIENT_DIR)/*.cpp)
SRC_SERVER_FILES = $(wildcard $(SRC_SERVER_DIR)/*.cpp)
SRC_MIXINS_FILES = $(wildcard $(SRC_MIXINS_DIR)/*.cpp)
OTMP_CLIENT = $(patsubst %.cpp,%.o,$(SRC_CLIENT_FILES:$(SRC_CLIENT_DIR)/%=%))
OTMP_SERVER = $(patsubst %.cpp,%.o,$(SRC_SERVER_FILES:$(SRC_SERVER_DIR)/%=%))
OTMP_MIXINS = $(patsubst %.cpp,%.o,$(SRC_MIXINS_FILES:$(SRC_MIXINS_DIR)/%=%))
OBJ_SERVER_FILES = $(patsubst %,$(OBJ_SERVER_DIR)/%,$(OTMP_SERVER))
OBJ_CLIENT_FILES = $(patsubst %,$(OBJ_CLIENT_DIR)/%,$(OTMP_CLIENT))
OBJ_MIXINS_FILES = $(patsubst %,$(OBJ_MIXINS_DIR)/%,$(OTMP_MIXINS))

all: server client

init:
	@echo $(UNAME)
	mkdir -p $(INSTALL_DIR)
	mkdir -p $(OBJ_MIXINS_DIR)

init_server: init
	@echo Initializing server...
	mkdir -p $(OBJ_SERVER_DIR)

init_client: init
	@echo Initializing client...
	mkdir -p $(OBJ_CLIENT_DIR)

server: init_server $(OBJ_SERVER_FILES) $(OBJ_MIXINS_FILES)
	$(CC) -o build/server $(OBJ_SERVER_FILES) $(OBJ_MIXINS_FILES) $(LIBS_SERVER)

client: init_client $(OBJ_CLIENT_FILES) $(OBJ_MIXINS_FILES)
	$(CC) -o build/client $(OBJ_CLIENT_FILES) $(OBJ_MIXINS_FILES) $(LIBS_CLIENT)

clean:
	@echo Clearing...
	rm -rf $(OBJ_SERVER_DIR)
	rm -rf $(OBJ_CLIENT_DIR)
	rm -rf $(OBJ_MIXINS_DIR)

$(OBJ_SERVER_DIR)/%.o: $(SRC_SERVER_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES_SERVER) $(LIBS_SERVER) -o $@ -c $<

$(OBJ_CLIENT_DIR)/%.o: $(SRC_CLIENT_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES_CLIENT) $(LIBS_CLIENT) -o $@ -c $<

$(OBJ_MIXINS_DIR)/%.o: $(SRC_MIXINS_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDES_MIXINS) $(LIBS_MIXINS) -o $@ -c $<
