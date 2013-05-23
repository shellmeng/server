CC=g++
CFLAGS=-g
OBJS = c_asyn_server.o  c_asyn_main.cpp netHeader.o
TARGET = asyn_server
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)


