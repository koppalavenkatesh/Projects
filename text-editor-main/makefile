CPP=g++
FLAGS=-O5 
RM= rm -f
EXEC = editorExec
OBJECTS = main Editor Buffer

all: $(OBJECTS) compile touch

main: main.cpp
		$(CPP) $(FLAGS) -c $@.cpp -o $@
Editor: Editor.cpp
		$(CPP) $(FLAGS) -c $@.cpp -o $@
Buffer: Buffer.cpp 
		$(CPP) $(FLAGS) -c $@.cpp -o $@

compile:
	$(CPP) $(FLAGS) $(OBJECTS) -o $(EXEC) -lncurses

clean:
	$(RM) $(OBJECTS) $(EXEC)

clean-no-exec:
	$(RM) $(OBJECTS)

compile-all :
	g++ *.cpp

touch:
	@echo " "
	@echo "Compilation done successfully..................."
