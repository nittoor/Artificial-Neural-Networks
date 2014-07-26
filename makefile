OBJS = AlphaData.o Alpha.o Helper.o Topography.o BackPropagation.o Source.o
CC = g++
DEBUG = -g
CFLAGS = -c $(DEBUG)
LFLAGS = $(DEBUG)

assign4 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o hw4
	
Source.o : Source.cpp
	$(CC) $(CFLAGS) Source.cpp

BackPropagation.o : BackPropagation.h BackPropagation.cpp
	$(CC) $(CFLAGS) BackPropagation.cpp
	
Topography.o : Topography.h Topography.cpp
	$(CC) $(CFLAGS) Topography.cpp
	
Helper.o : Helper.h Helper.cpp
	$(CC) $(CFLAGS) Helper.cpp
	
Alpha.o : Alpha.h Alpha.cpp
	$(CC) $(CFLAGS) Alpha.cpp

AlphaData.o : AlphaData.h AlphaData.cpp
	$(CC) $(CFLAGS) AlphaData.cpp

clean:
	\rm *.o hw4
