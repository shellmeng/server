CC=g++
CFLAGS=-g
OBJS = netHeader.o c_asyn_server.o c_asyn_main.cpp 
TARGET = asyn_server
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) *.o


