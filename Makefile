CC=g++
CFLAGS=-Wextra -Wall -std=c++14
sfmlso=-lsfml-graphics -lsfml-window -lsfml-system
OBJS=main.o scene.o scenemanager.o texturemanager.o complexTypes.o
OBJDIR=obj

ifdef ComSpec
appname=snake.exe
removeObj=del /Q obj\*
mkobjdir=@if not exist obj\\ mkdir obj\\
else
appname=snake.out
removeObj=rm ./obj/*
mkobjdir=mkdir -p obj/
endif 

OBJ = $(addprefix $(OBJDIR)/, $(OBJS))

.PHONY : clean prepare

all linux: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(sfmlso) -o $(appname)

windows: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(sfmlso) -o $(appname)

$(OBJDIR)/main.o: main.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/scene.o: Scene/Scene.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/scenemanager.o: SceneManager/SceneManager.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/texturemanager.o: TextureManager/TextureManager.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/complexTypes.o: utility/complexTypes.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	$(removeObj)

prepare:
	$(mkobjdir)
