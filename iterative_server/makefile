CC=g++
CFLAGS=-g
OBJS = c_iterative_server.o  c_iterative_main.cpp netHeader.o
TARGET = iter_server
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)


