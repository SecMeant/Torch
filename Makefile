CC=g++
CFLAGS=-Wextra -Wall -std=c++14
sfmlso=-lsfml-graphics -lsfml-window -lsfml-system
OBJS=main.o scene.o scenemanager.o texturemanager.o complexTypes.o\
		 mainscene.o gamescene.o player.o moveable.o dynamicsprite.o\
		 motionsprite.o
OBJDIR=obj

ifdef ComSpec
appname=torch.exe
removeObj=del /Q obj\*
mkobjdir=@if not exist obj\\ mkdir obj\\
else
appname=torch.out
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

$(OBJDIR)/gamescene.o: Scene/GameScene/GameScene.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/mainscene.o: Scene/MainScene/MainScene.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/scenemanager.o: SceneManager/SceneManager.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/texturemanager.o: TextureManager/TextureManager.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/dynamicsprite.o: TextureManager/DynamicSprite/DynamicSprite.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/motionsprite.o: TextureManager/DynamicSprite/MotionSprite/MotionSprite.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/player.o: Player/Player.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/moveable.o: Interfaces/Moveable/Moveable.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/complexTypes.o: utility/complexTypes.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	$(removeObj)

prepare:
	$(mkobjdir)
