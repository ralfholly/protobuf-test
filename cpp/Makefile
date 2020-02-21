TARGET := CurrentDateTimeTest
PROTO := current_date_time
CC := g++
CPPFLAGS := -W -Wall -g -pthread -I/usr/local/include
SERFILE := protobuftest.cpp.ser
LDLIBS := -L/usr/local/lib -lprotobuf -lpthread

$(TARGET): $(TARGET).o $(PROTO).pb.o

$(TARGET).o: $(TARGET).cpp $(PROTO).pb.h

$(PROTO).pb.o: $(PROTO).pb.cc $(PROTO).pb.h

$(PROTO).pb.h: ../$(PROTO).proto
	protoc --cpp_out . -I .. $<

.PHONY: test
test: $(TARGET)
	./$< $(SERFILE)

.PHONY: clean
clean:
	rm -rf $(TARGET) *.o $(PROTO).pb.* $(SERFILE) $(SERFILE).json
