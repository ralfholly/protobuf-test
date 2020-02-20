TARGET := CurrentDateTimeTest
PROTO := current_date_time
PROTOLIBTAR := protobuf-java-3.11.4.jar
PROTOIF := com/example/protobuftest/CurrentDateTime.java
SERFILE = /tmp/protobuftest.java.ser

export CLASSPATH := $(CLASSPATH):$(PROTOLIBTAR)

$(TARGET): $(TARGET).java $(PROTOIF)
	javac $^

$(PROTOIF): ../$(PROTO).proto
	protoc --java_out . -I .. $<

.PHONY: test
test: $(TARGET)
	java $< $(SERFILE)

.PHONY: clean
clean:
	rm -rf *.class $(PROTOIF) $(SERFILE)
