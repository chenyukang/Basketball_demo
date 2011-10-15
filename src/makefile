CC=g++ -g -Wall
CFLAGS= -c 
LIB= -lm -lglut -lglui

OBJS =  main.o Game.o Grapic.o \
	BaseGameEntity.o BasketBall.o \
	BallTeam.o EntityManager.o \
	FieldPlayer.o PlayerBase.o \
	Messages.o FrameCounter.o \
	SteeringBehavior.o PrecisionTimer.o \
	TeamState.o FieldPlayerStates.o \
	MessageDispatcher.o\

Game : $(OBJS)
	$(CC) $(OBJS) -o Game $(LIB)

clean:
	rm -rf ${OBJS} Game
