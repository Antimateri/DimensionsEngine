DEBUG?=

compile: generation.o main.o
	g++ -c ../src/main.cpp -o main.o -I../src $(DEBUG)
	g++ logic.o control.o generation.o graphic.o main.o -o main -I../src -lSDL2 $(DEBUG)

graphic: graphic.o

logic: logic.o
	g++ -c ../src/logic/main.cpp -o mainLogic.o -I../src $(DEBUG)
	g++ mainLogic.o logic.o -o mainLogic -I../src $(DEBUG)

control: control.o

generation.o: graphic.o

graphic.o: control.o
	g++ -c ../src/graphic/mainWindow.cpp -o ./mainWindow.o -I../src

control.o: logic.o

logic.o:
	g++ -c ../src/logic/objects/components/component.cpp -o ./component.o -I../src $(DEBUG)
	g++ -c ../src/logic/objects/world.cpp -o ./world.o -I../src $(DEBUG)
	g++ -c ../src/logic/automata/states.cpp -o ./fsm.o -I../src $(DEBUG)
	g++ -c ../src/library.cpp -o ./library.o -I../src $(DEBUG)
	g++ -c ../src/logic/game.cpp -o ./game.o -I../src $(DEBUG)
	g++ -c ../src/logic/algorithms.cpp -o ./algorithm.o -I../src $(DEBUG)
	ld -r ./component.o ./world.o ./fsm.o ./library.o ./game.o ./algorithm.o -o ./logic.o $(DEBUG)

main.o:
	g++ -c ../src/main.cpp -o main.o -I../src

debug:
	g++ -g -o main $$(find ../src -print | grep .cpp$$ ) -I../src -lSDL2

debugW:
	g++ -g -o main $$(find ../src -print | grep .cpp$$ ) -I../src -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -lSDL2

clear:
	-rm ./*.o
