compile: graphic.o world.o game.o main.o
	g++ ./*.o -o main -I../src -lSDL2

graphic.o: render.o textureManager.o
	g++ -c ../src/graphic/mainWindow.cpp -o ./mainWindow.o -I../src

render.o:
	g++ -c ../src/graphic/renderers/toRenderBackground.cpp -o ./toRenderBackground.o -I../src
	g++ -c ../src/graphic/renderer.cpp -o ./renderer.o -I../src
	g++ -c ../src/graphic/renderers/toRenderEntities.cpp -o ./toRenderEntities.o -I../src

textureManager.o:
	g++ -c ../src/graphic/textureManager.cpp -o ./textureManager.o -I../src

world.o: components.o
	g++ -c ../src/logic/objects/world.cpp -o ./world.o -I../src

components.o:
	g++ -c ../src/logic/objects/components/component.cpp -o ./component.o -I../src 

game.o: 
	g++ -c ../src/logic/game.cpp -o ./game.o -I../src

main.o:
	g++ -c ../src/main.cpp -o main.o -I../src

debug:
	g++ -g -o main $$(find ../src -print | grep .cpp$$ ) -I../src -lSDL2

debugW:
	g++ -g -o main $$(find ../src -print | grep .cpp$$ ) -I../src -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -lSDL2

clear:
	-rm ./*.o
	rm ./main
