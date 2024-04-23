
#
# Makefile for Registering Teams, ecs36b, s2024
#

CC = g++ -std=c++14
CFLAGS = -g -g -I/opt/homebrew/include

# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

# CORE_INCS =	Core.h Transaction.h Person.h
# CORE_OBJS =	Core.o Transaction.o Person.o
# SHADOW_INCS = Shadow_Flight.h Shadow_Person.h
# SHADOW_OBJS = Shadow_Flight.o Shadow_Person.o 

LDFLAGS = -L/opt/homebrew/lib -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

# rules.
all: 	rtclient rtserver

#
#

rtclient.h:		ecs36b_rt.json
	jsonrpcstub ecs36b_rt.json --cpp-server=rtServer --cpp-client=rtClient

rtserver.h:		ecs36b_rt.json
	jsonrpcstub ecs36b_rt.json --cpp-server=rtServer --cpp-client=rtClient

ecs36b_JSON.o:		ecs36b_JSON.cpp ecs36b_Common.h ecs36b_Exception.h
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

JvTime.o:		JvTime.cpp JvTime.h ecs36b_Common.h ecs36b_Exception.h
	$(CC) -c $(CFLAGS) JvTime.cpp

ecs36b_Exception.o:	ecs36b_Exception.cpp ecs36b_Common.h ecs36b_Exception.h
	$(CC) -c $(CFLAGS) ecs36b_Exception.cpp

rtclient.o:		rtclient.h rtclient.cpp
	$(CC) -c $(CFLAGS) rtclient.cpp

rtserver.o:		rtserver.h rtserver.cpp
	$(CC) -c $(CFLAGS) rtserver.cpp

rtclient:		rtclient.o ecs36b_JSON.o JvTime.o ecs36b_Exception.o
	$(CC) -o rtclient rtclient.o ecs36b_JSON.o ecs36b_Exception.o JvTime.o $(LDFLAGS)

rtserver:		rtserver.o ecs36b_JSON.o JvTime.o ecs36b_Exception.o
	$(CC) -o rtserver rtserver.o ecs36b_JSON.o ecs36b_Exception.o JvTime.o $(LDFLAGS)

clean:
	rm -f *.o *~ core rtclient rtserver rtclient.h rtserver.h
