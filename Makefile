CC = g++
COPTFLAGS = -O3 -g

default:
	@echo "================================================="
	@echo "To build your program, use:"
	@echo "  make prim          #For prim's algorithm test"
	@echo ""
	@echo "To clean this directory (remove object files"
	@echo "and other junk), use:"
	@echo " make clean"
	@echo "================================================="

# prim's algorithm
prim: BHeap.o prim.o prim_d.cc
	$(CC) $(COPTFLAGS) -o $@ $^

# Binary Heap functions
BHeap.o: BHeap.cc
	$(CC) $(COPTFLAGS) -o $@ -c $<

# prim's algorithm functions
prim.o: prim.cc
	$(CC) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ prim mst.txt

#eof
