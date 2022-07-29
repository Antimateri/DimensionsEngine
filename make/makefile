compile: graphic.o world.o game.o main.o
	g++ ./*.o -o main -I../include -lSDL2

graphic.o: render.o textureManager.o
	g++ -c ../src/graphic/mainWindow.cpp -o ./mainWindow.o -I../include

render.o:
	g++ -c ../src/graphic/renderers/toRenderBackground.cpp -o ./toRenderBackground.o -I../include
	g++ -c ../src/graphic/renderer.cpp -o ./renderer.o -I../include
	g++ -c ../src/graphic/renderers/toRenderEntities.cpp -o ./toRenderEntities.o -I../include

textureManager.o:
	g++ -c ../src/graphic/textureManager.cpp -o ./textureManager.o -I../include

world.o: components.o
	g++ -c ../src/logic/objects/world.cpp -o ./world.o -I../include

components.o:
	g++ -c ../src/logic/objects/components/component.cpp -o ./component.o -I../include 

game.o: 
	g++ -c ../src/logic/game.cpp -o ./game.o -I../include

main.o:
	g++ -c ../src/main.cpp -o main.o -I../include

debug:
	g++ -g -o main $$(find ../src -print | grep .cpp) -I../include -lSDL2

debugW:
	g++ -g -o main $$(find ../src -print | grep .cpp) -I../include -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -lSDL2

clear:
	-rm ./*.o
	rm ./main