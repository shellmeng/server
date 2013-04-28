CC=g++
CFLAGS=-g
OBJS = solution.o plant.o main.o eleNet.o instance.o algorithmForPower.o random.o context.o
TARGET = power
RM=rm -f

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS): %.o:%.cpp 
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	-$(RM) $(TARGET) $(OBJS)


