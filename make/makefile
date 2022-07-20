compile: graphic.o world.o game.o main.o
	g++ -g ./*.o -o main -I../include -lSDL2

graphic.o: render.o textureManager.o
	g++ -g -c ../src/graphic/mainWindow.cpp -o ./mainWindow.o -I../include

render.o:
	g++ -g -c ../src/graphic/renderers/toRenderBackground.cpp -o ./toRenderBackground.o -I../include
	g++ -g -c ../src/graphic/renderer.cpp -o ./renderer.o -I../include
	g++ -g -c ../src/graphic/renderers/toRenderEntities.cpp -o ./toRenderEntities.o -I../include

textureManager.o:
	g++ -g -c ../src/graphic/textureManager.cpp -o ./textureManager.o -I../include

world.o: components.o
	g++ -g -c ../src/logic/objects/world.cpp -o ./world.o -I../include

components.o:
	g++ -g -c ../src/logic/objects/components/component.cpp -o ./component.o -I../include 

game.o: 
	g++ -g -c ../src/logic/game.cpp -o ./game.o -I../include

main.o:
	g++ -g -c ../src/main.cpp -o main.o -I../include

clear:
	rm ./*.o
	rm ./main