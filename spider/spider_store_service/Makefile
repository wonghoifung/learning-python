TARGET = store_server

PREFIX_BIN =

CXX=g++  

ifeq (0,${debug}) 
	CPPFLAGS = -DNDEBUG -g2 -O2 
else
	CPPFLAGS = -ggdb -O2 
endif 

CPPFLAGS += -Wall -DHAVE_NETINET_IN_H 
CPPFLAGS += -I../env/boost/include/
CPPFLAGS += -I../env/jsoncpp/include/
CPPFLAGS += -I../env/mysqlpp/include/
CPPFLAGS += -I../env/mysqlconnector/include/
CPPFLAGS += -I../env/thrift/include/
CPPFLAGS += -I../env/libevent/include/
CPPFLAGS += -I../env/thrift/include/thrift/

LIBS = -lboost_date_time -lboost_system -lboost_thread -lboost_regex -lrt -ljson -lmysqlpp -lmysqlclient -lshared_utils -lthriftnb -levent -lthrift
LINKFLAGS = -L/usr/local/lib 
LINKFLAGS += -L../env/boost/lib/
LINKFLAGS += -L../env/jsoncpp/libs/linux-gcc-4.4.7/
LINKFLAGS += -L../env/mysqlpp/lib/
LINKFLAGS += -L../env/mysqlconnector/lib/
LINKFLAGS += -L../env/
LINKFLAGS += -L../env/libevent/lib/
LINKFLAGS += -L../env/thrift/lib/

INCLUDEDIRS = ./ ../
INCLUDES = $(foreach tmp, $(INCLUDEDIRS), -I $(tmp))

MYSOURCEDIRS = ./

SOURCEDIRS = $(MYSOURCEDIRS)


C_SOURCES = $(foreach tmp, $(SOURCEDIRS), $(wildcard $(tmp)*.c))
C_OBJS = $(patsubst %.c, %.o, $(C_SOURCES))


CPP_SOURCES = $(foreach tmp, $(SOURCEDIRS), $(wildcard $(tmp)*.cpp))
CPP_OBJS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))

all:compile
.PHONY :all

.c.o:
	$(CC) -c -o $*.o $(CFLAGS) $(INCLUDES) $*.c
.cpp.o:
	$(CXX) -c -o $*.o $(CPPFLAGS) $(INCLUDES) $*.cpp

compile: $(CPP_OBJS) $(C_OBJS) $(OTHERS_C_OBJS) $(OTHERS_CPP_OBJS)
	$(CXX) $(LINKFLAGS) -o $(TARGET) $^ $(LIBS)

.PHONY : clean
clean:
	rm -f $(CPP_OBJS) $(C_OBJS)
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(PREFIX_BIN)

uninstall:
	rm -f $(PREFIX)/$(PREFIX_BIN)

rebuild: clean

