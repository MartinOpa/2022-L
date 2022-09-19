TARGET=threads

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	g++ -g -pthread $^ -o $@

clean:
	rm -rf $(TARGET)
