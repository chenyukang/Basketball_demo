CC=g++
CFLAGS= -c 
LIB= -lm -lglut -lglui
Game: main.o Game.o Grapic.o BaseGameEntity.o BasketBall.o BallTeam.o EntityManager.o \
	FieldPlayer.o PlayerBase.o 
	$(CC) main.o Game.o Grapic.o BaseGameEntity.o BasketBall.o \
              BallTeam.o EntityManager.o FieldPlayer.o PlayerBase.o \
	 -o Game  $(LIB)

Game.o: Game.h Game.cpp Region.h Goal.h Grapic.h BasketBall.h BallTeam.h
	$(CC) $(CFLAGS)  Game.cpp

Grapic.o: Grapic.h Grapic.cpp
	$(CC) $(CFLAGS) Grapic.cpp

main.o: main.cpp
	$(CC) $(CFLAGS)  main.cpp

BaseGameEntity.o: BaseGameEntity.h BaseGameEntity.cpp
	$(CC) $(CFLAGS) BaseGameEntity.cpp

BasketBall.o: BasketBall.h Grapic.h BasketBall.cpp 
	$(CC) $(CFLAGS) BasketBall.cpp

BallTeam.o: BallTeam.h BallTeam.cpp PlayerBase.h Goal.h Game.h
	$(CC) $(CFLAGS) BallTeam.cpp

EntityManager.o: EntityManager.h EntityManager.cpp
	$(CC) $(CFLAGS) EntityManager.cpp

FieldPlayer.o: FieldPlayer.h PlayerBase.h BasketBall.h BallTeam.h
	$(CC) $(CFLAGS) FieldPlayer.cpp

PlayerBase.o: autolist.h Vec2D.h MovingEntity.h PlayerBase.cpp
	$(CC) $(CFLAGS) PlayerBase.cpp
clean:
	rm *.o
