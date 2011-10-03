CC=g++ -g
CFLAGS= -c 
LIB= -lm -lglut -lglui
Game: main.o Game.o Grapic.o BaseGameEntity.o BasketBall.o BallTeam.o EntityManager.o \
	FieldPlayer.o PlayerBase.o \
	constants.o Messages.o FrameCounter.o MessageDispatcher.o \
	SteeringBehavior.o FrameCounter.o PrecisionTimer.o TeamState.o  \
	FieldPlayerStates.o \

	$(CC) main.o Game.o Grapic.o BaseGameEntity.o BasketBall.o \
              BallTeam.o EntityManager.o FieldPlayer.o PlayerBase.o \
	      Messages.o FrameCounter.o PrecisionTimer.o SteeringBehavior.o \
	      TeamState.o FieldPlayerStates.o \
	 -o Game  $(LIB)

# main.o: main.cpp
# 	$(CC) $(CFLAGS) main.cpp

# Game.o: Game.h Game.cpp Region.h Goal.h Grapic.h BasketBall.h BallTeam.h
# 	$(CC) $(CFLAGS) Game.cpp

# Grapic.o: Grapic.h Grapic.cpp
# 	$(CC) $(CFLAGS) Grapic.cpp

# BaseGameEntity.o: BaseGameEntity.h BaseGameEntity.cpp
# 	$(CC) $(CFLAGS) BaseGameEntity.cpp

# BasketBall.o: BasketBall.h Grapic.h BasketBall.cpp 
# 	$(CC) $(CFLAGS) BasketBall.cpp

# BallTeam.o: BallTeam.h BallTeam.cpp PlayerBase.h Goal.h Game.h
# 	$(CC) $(CFLAGS) BallTeam.cpp

# EntityManager.o: EntityManager.h EntityManager.cpp
# 	$(CC) $(CFLAGS) EntityManager.cpp

# FieldPlayer.o: FieldPlayer.h PlayerBase.h BasketBall.h BallTeam.h FieldPlayer.cpp
# 	$(CC) $(CFLAGS) FieldPlayer.cpp

# PlayerBase.o: autolist.h Vec2D.h MovingEntity.h PlayerBase.cpp
# 	$(CC) $(CFLAGS) PlayerBase.cpp

# Messages.o: Messages.h Messages.cpp
# 	$(CC) $(CFLAGS) Messages.cpp

clean:
	rm *.o
