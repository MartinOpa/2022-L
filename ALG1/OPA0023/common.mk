OUT = bin

SEARCHPATH += src
vpath %.cpp $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += main.h

_OBJS += main.o
_OBJS += shuntingYard.o
_OBJS += postfix.o

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

all: $(PROG)

$(OUT)/%.o: %.cpp %.h $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<
	
clean:
	$(RM) -rf $(OUT) $(PROG)
