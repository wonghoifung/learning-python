TARGET = store_server

PREFIX_BIN =

CXX=g++  

ifeq (0,${debug}) 
	CPPFLAGS = -DNDEBUG -g2 -O2 
else
	CPPFLAGS = -ggdb -O2 
endif 

CPPFLAGS += -Wall -DHAVE_NETINET_IN_H 
CPPFLAGS += -I/home/albert/env/boost/include/
CPPFLAGS += -I/home/albert/env/jsoncpp/include/
CPPFLAGS += -I/home/albert/env/mysqlpp/include/
CPPFLAGS += -I/home/albert/env/mysqlconnector/include/
CPPFLAGS += -I/home/albert/env/thrift/include/
CPPFLAGS += -I/home/albert/env/libevent/include/
CPPFLAGS += -I/home/albert/env/thrift/include/thrift/

LIBS = -lboost_date_time -lboost_system -lboost_thread -lrt -ljson -lmysqlpp -lmysqlclient -lshared_utils -lthriftnb -levent -lthrift
LINKFLAGS = -L/usr/local/lib 
LINKFLAGS += -L/home/albert/env/boost/lib/
LINKFLAGS += -L/home/albert/env/jsoncpp/libs/linux-gcc-4.4.7/
LINKFLAGS += -L/home/albert/env/mysqlpp/lib/
LINKFLAGS += -L/home/albert/env/mysqlconnector/lib/
LINKFLAGS += -L/home/albert/env/
LINKFLAGS += -L/home/albert/env/libevent/lib/
LINKFLAGS += -L/home/albert/env/thrift/lib/

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

