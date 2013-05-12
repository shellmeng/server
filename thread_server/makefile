CC=g++
CFLAGS=-g -lpthread
OBJS = netHeader.o c_thread_server.o c_thread_main.cpp 
TARGET = thread_server
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) *.o


