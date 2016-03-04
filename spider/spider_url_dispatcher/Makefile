TARGET = dispatcher

PREFIX_BIN =

CXX=g++  

ifeq (0,${debug}) 
	CPPFLAGS = -DNDEBUG -g2 -O2 
else
	CPPFLAGS = -ggdb -O2 
endif 

CPPFLAGS += -Wall
CPPFLAGS += -I../env/boost/include/
CPPFLAGS += -I../env/jsoncpp/include/
CPPFLAGS += -I../env/hiredis/include/hiredis/
CPPFLAGS += -I../env/protobuf/include/

LIBS = -lboost_date_time -lboost_system -lboost_thread -luuid -lrt -ljson -lhiredis -lprotobuf -lshared
LINKFLAGS = -L/usr/local/lib 
LINKFLAGS += -L../env/boost/lib/ 
LINKFLAGS += -L../env/jsoncpp/libs/linux-gcc-4.4.7/
LINKFLAGS += -L../env/hiredis/lib/
LINKFLAGS += -L../env/protobuf/lib/
LINKFLAGS += -L../env/

INCLUDEDIRS = ./ ../ ../shared/protocol/ ../shared/net/ ../shared/utils/ ./pb/
INCLUDES = $(foreach tmp, $(INCLUDEDIRS), -I $(tmp))

MYSOURCEDIRS = ./ ./pb/

SOURCEDIRS = $(MYSOURCEDIRS)

C_SOURCES = $(foreach tmp, $(SOURCEDIRS), $(wildcard $(tmp)*.c))
C_OBJS = $(patsubst %.c, %.o, $(C_SOURCES))

CPP_SOURCES = $(foreach tmp, $(SOURCEDIRS), $(wildcard $(tmp)*.cpp))
CPP_OBJS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))

CC_SOURCES = $(foreach tmp, $(SOURCEDIRS), $(wildcard $(tmp)*.cc))
CC_OBJS = $(patsubst %.cc, %.o, $(CC_SOURCES))

all:compile
.PHONY :all

.c.o:
	$(CC) -c -o $*.o $(CFLAGS) $(INCLUDES) $*.c
.cpp.o:
	$(CXX) -c -o $*.o $(CPPFLAGS) $(INCLUDES) $*.cpp
.cc.o:
	$(CXX) -c -o $*.o $(CPPFLAGS) $(INCLUDES) $*.cc

compile: $(CPP_OBJS) $(CC_OBJS) $(C_OBJS) $(OTHERS_C_OBJS) $(OTHERS_CPP_OBJS)
	$(CXX) $(LINKFLAGS) -o $(TARGET) $^ $(LIBS)

.PHONY : clean
clean:
	rm -f $(CPP_OBJS) $(CC_OBJS) $(C_OBJS)
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(PREFIX_BIN)

uninstall:
	rm -f $(PREFIX)/$(PREFIX_BIN)

rebuild: clean

