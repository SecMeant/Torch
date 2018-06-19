CC=g++
CFLAGS=-Wextra -Wall -std=c++14 -O3
sfmlso=-lsfml-graphics -lsfml-window -lsfml-system
OBJS=main.o scene.o scenemanager.o texturemanager.o complexTypes.o\
		 mainscene.o gamescene.o player.o moveable.o dynamicsprite.o\
		 motionsprite.o level.o lightsource.o object.o mapobject.o\
		 lightmanager.o otorch.o testunit.o dynamicobject.o statsobject.o
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

$(OBJDIR)/object.o: Object/Object.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/dynamicobject.o: Object/DynamicObject/DynamicObject.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/otorch.o: Object/Torch/OTorch.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/mapobject.o: Object/MapObject/MapObject.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/level.o: Level/Level.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/moveable.o: Interfaces/Moveable/Moveable.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/dropable.o: Interfaces/Dropable/Dropable.hpp
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/lightsource.o: Interfaces/LightSource/LightSource.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/lightmanager.o: LightManager/LightManager.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/complexTypes.o: utility/complexTypes.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/statsobject.o: Scene/GameScene/StatsObject/StatsObject.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

$(OBJDIR)/testunit.o: Tests/TestUnit.cc
	$(CC) -c $^ -o $@ $(CFLAGS)

clean:
	$(removeObj)

prepare:
	$(mkobjdir)
