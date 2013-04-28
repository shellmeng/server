CC=g++
CFLAGS=-g
OBJS = c_iterative_client.o  c_iterative_client_main.cpp netHeader.o
TARGET = iter_client
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)


