CC=g++
CFLAGS=-g
OBJS = netHeader.o c_process_server.o c_process_main.cpp 
TARGET = process_server
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) *.o


