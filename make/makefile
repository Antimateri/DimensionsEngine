DEBUG?=
F?=noFlags
FLAGS=$$(cat $F)

all: generation.o
	g++ $(FLAGS) -c ../src/main.cpp -o main.o -I../src $(DEBUG)
	g++ $(FLAGS) logic.o control.o generation.o graphic.o main.o -o main -I../src -lSDL2 $(DEBUG)

graphic: graphic.o
	g++ $(FLAGS) -c ../src/graphic/main.cpp -o mainGraphic.o -I../src $(DEBUG)
	g++ $(FLAGS) mainGraphic.o graphic.o logic.o control.o -o mainGraphic -I../src $(DEBUG)

logic: logic.o
	g++ $(FLAGS) -c ../src/logic/main.cpp -o mainLogic.o -I../src $(DEBUG)
	g++ $(FLAGS) mainLogic.o logic.o -o mainLogic -I../src $(DEBUG)

control: control.o
	g++ $(FLAGS) -c ../src/control/main.cpp -o ./mainControl.o -I../src $(DEBUG)
	g++ $(FLAGS) mainControl.o logic.o control.o -o mainControl -I../src $(DEBUG)
 
generation.o: graphic.o
	g++ $(FLAGS) -c ../src/generation/biomeFactory.cpp -o biomeFactory.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/generation/caveFactory.cpp -o caveFactory.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/generation/dungeonFactory.cpp -o dungeonFactory.o -I../src $(DEBUG)
	ld -r ./biomeFactory.o ./caveFactory.o ./dungeonFactory.o -o ./generation.o $(DEBUG)

graphic.o: control.o
	g++ $(FLAGS) -c ../src/control/commandComponents/animationsCommandComponents.cpp -o animCommands.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/animation/innerAnimation.cpp -o innerAnimation.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/animation/outerAnimation.cpp -o outerAnimation.o -I../src $(DEBUG)
	ld -r ./animCommands.o ./innerAnimation.o ./outerAnimation.o -o ./animation.o $(DEBUG)

	g++ $(FLAGS) -c ../src/graphic/toRender/toRenderAnimation.cpp -o toRenderAnimation.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/toRender/toRenderBackground.cpp -o toRenderBackground.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/toRender/toRenderEntities.cpp -o toRenderEntities.o -I../src $(DEBUG)
	ld -r ./toRenderAnimation.o ./toRenderBackground.o ./toRenderEntities.o -o ./toRender.o $(DEBUG)

	g++ $(FLAGS) -c ../src/graphic/IO.cpp -o IO.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/mainWindow.cpp -o mainWindow.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/renderer.cpp -o renderer.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/graphic/textureManager.cpp -o textureManager.o -I../src $(DEBUG)
	ld -r ./IO.o ./mainWindow.o ./renderer.o ./textureManager.o -o ./graphicInterface.o $(DEBUG)

	ld -r ./animation.o ./toRender.o ./graphicInterface.o -o ./graphic.o $(DEBUG)

control.o: logic.o
	g++ $(FLAGS) -c ../src/logic/objects/components/controlComponents.cpp -o ./controlComponents.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/logic/engines/behaviour/behaviourEngineCommand.cpp -o ./behEngine.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/control/command.cpp -o ./command.o -I../src $(DEBUG)

	g++ $(FLAGS) -c ../src/control/commandComponents/miscellaneusCommandComponents.cpp -o ./miscComponents.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/control/commandComponents/moveCommandComponents.cpp -o ./movComponents.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/control/commandComponents/targetCommandComponents.cpp -o ./tarComponents.o -I../src $(DEBUG)
	ld -r ./miscComponents.o ./movComponents.o ./tarComponents.o -o ./components.o $(DEBUG)

	g++ $(FLAGS) -c ../src/control/control.cpp -o ./controlInterface.o -I../src $(DEBUG)
	ld -r ./behEngine.o ./command.o ./components.o ./controlInterface.o ./controlComponents.o -o ./control.o $(DEBUG)

logic.o:
	g++ $(FLAGS) -c ../src/logic/objects/components/component.cpp -o ./component.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/logic/objects/world.cpp -o ./world.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/logic/automata/states.cpp -o ./fsm.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/library.cpp -o ./library.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/logic/game.cpp -o ./game.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/logic/algorithms.cpp -o ./algorithm.o -I../src $(DEBUG)
	g++ $(FLAGS) -c ../src/logic/engines/behaviour/goap/goals/planningParameter.cpp -o ./planningParameter.o -I../src $(DEBUG)
	ld -r ./component.o ./world.o ./fsm.o ./library.o ./game.o ./algorithm.o ./planningParameter.o -o ./logic.o $(DEBUG)

debug:
	g++ $(FLAGS) -g -o main $$(find ../src -print | grep .cpp$$ ) -I../src -lSDL2

debugW:
	g++ $(FLAGS) -g -o main $$(find ../src -print | grep .cpp$$ ) -I../src -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -lSDL2

clear:
	-rm $(FLAGS) ./*.o
