TARGET = libshared_utils.a

PREFIX_BIN = /home/albert/env/

CXX=g++  

ifeq (0,${debug}) 
	CPPFLAGS = -DNDEBUG -g2 -O2 
else
	CPPFLAGS = -ggdb -O2 
endif 

CPPFLAGS += -Wall
CPPFLAGS += -I/home/albert/env/boost/include/
CPPFLAGS += -I/home/albert/env/jsoncpp/include/

LIBS = -lboost_date_time -lboost_system -lrt -ljson 
LINKFLAGS = -L/usr/local/lib 
LINKFLAGS += -L/home/albert/env/boost/lib/ 
LINKFLAGS += -L/home/albert/env/jsoncpp/libs/linux-gcc-4.4.7/

INCLUDEDIRS = ./ ../ ./utils/ 
INCLUDES = $(foreach tmp, $(INCLUDEDIRS), -I $(tmp))

MYSOURCEDIRS = ./ ./utils/ 

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
	ar -rc $(TARGET) $^ 

.PHONY : clean
clean:
	rm -f $(CPP_OBJS) $(C_OBJS)
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) $(PREFIX_BIN)

uninstall:
	rm -f $(PREFIX)/$(PREFIX_BIN)/$(TARGET)

rebuild: clean

