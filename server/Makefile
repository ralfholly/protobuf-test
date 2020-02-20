TARGET := server
PROTO := current_date_time
CC := g++
CPPFLAGS := -W -Wall -g -pthread -I/usr/local/include

LDLIBS := -L/usr/local/lib -lprotobuf

$(TARGET): $(TARGET).o $(PROTO).pb.o

$(TARGET).o: $(TARGET).cpp $(PROTO).pb.h

$(PROTO).pb.o: $(PROTO).pb.cc $(PROTO).pb.h

$(PROTO).pb.h: ../$(PROTO).proto
	protoc --cpp_out . -I .. $<

.PHONY: test
test: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o $(PROTO).pb.*


