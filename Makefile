CXX=  g++

CFLAGS=-g -Wall -Iinclude/ -std=c++11
LDFLAGS=
LIBS=

O=build

OBJS= \
    $(O)/main.o

all: $(O)/project

clean:
	rm -rf $(O)

$(O)/project: $(OBJS) $(O)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(O)/project $(LIBS)

$(O)/%.o: src/%.cpp $(O)
	$(CXX) $(CFLAGS) -c $< -o $@

$(O):
	mkdir $(O)
