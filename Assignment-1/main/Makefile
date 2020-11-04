CC=clang++
CFLAGS=-Wall
OBJS=shared_mem.o
EXE=sender.elf receiver.elf destroy_mem.elf

all: $(EXE)

%.elf: %.o $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o $(EXE)