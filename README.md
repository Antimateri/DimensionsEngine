<div align="center">

# Dimensions engine

[Modules](#Modules) | [Usage](#usage) | [How to Build](#how-to-build)

</div>



This is a quite simple and quite generic (but intended to be used for rpg) game engine in development programmed in C++ in an attempt to understand the workings of a game engine and to experiment with different architectures and technologies
## **Modules**
***
- ### Logic
    The logic behind the game and information storage.
    Entities function via an entity-component architecture
    - **game**: in charge of using the different classes of the engine together
    - **world**: stores all the information regarding the actual state of the world: entities, components, map, background...
    - **components**: different characteristics an entity can have
    - **interfaces**: to interact with the output, input and control
- ### Control
    Using a command architecture
    - **command**: manages the execution of changes in the world
    - **commandComponents**: microcommands used by command to generate complex actions
    - **behaviourEngine**: planner and executioner following a GOAP (goal oriented action planning) architecture
- ### Graphic
    Based on SDL2, handles input and output
    - **animations**:
        divided in those which affect entities and those which not
    - **mainWindow**: to manage the game window
    - **toRender**: manages input and aoutput through layers following the toRender interface
    - **textureManager**: stores and draws textures
- ### Generation
    Procedural generation code for experimenting, unfinished

## **Usage**
****
This is a simple code to use most of the capabilities of the engine
```Cpp
int main(){
    //initialazing the modules
    game _game;
    _game.addControlUnit(new commandControl());
    _game.addIOUnit(new SDLIO());
    library._mainWindow=new mainWindow();

    //generating the world
    std::vector<biomeFactory*> factories;
    factories.push_back(new biomeFactory());
    factories.push_back(new caveFactory(45,5));
    _game.setWorld(dungeonFactory(factories).makeNew(1,10)); 

    //initialazing the graphic modules
    library._innerAnimationManager=new toRenderInnerAnimation();
    library._mainWindow->addLayer(library._innerAnimationManager);
    library._mainWindow->addLayer(new toRenderBackground(_game.getWorld()));
    library._mainWindow->addLayer(new toRenderEntities(&_game));
    library._outerAnimationManager=new toRenderOuterAnimation();
    library._mainWindow->addLayer(library._outerAnimationManager);

    //initialazing the player
    EntityID ent=_game.getWorld()->newEntity();
    _game.getWorld()->Assign<positionComponent>(ent)->moveTo(1,1,_game.getWorld(),ent);
    _game.getWorld()->Assign<currentActionComponent>(ent);
    _game.getWorld()->Assign<imageComponent>(ent)->img=library._textureManager->add();

    SDL_Renderer* r=library._textureManager->edit(&_game.getWorld()->Get<imageComponent>(ent)->img);
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r,&_game.getWorld()->Get<imageComponent>(ent)->img.getRect());

    library._player=ent;

    //initialazing a npc
    EntityID ent2=_game.getWorld()->newEntity();
    _game.getWorld()->Assign<positionComponent>(ent2)->moveTo(9,9,_game.getWorld(),ent2);
    _game.getWorld()->Assign<imageComponent>(ent2)->img=library._textureManager->add();
    _game.getWorld()->Assign<blockComponent>(ent2)->setBlock(directions::all);
    _game.getWorld()->Assign<currentActionComponent>(ent2);
    _game.getWorld()->Assign<actorComponent>(ent2)->addGoal((new planMove())->setOwner(ent2));
    _game.getWorld()->Assign<APComponent>(ent2)->setmax(20)->setVal(20);

    r=library._textureManager->edit(&_game.getWorld()->Get<imageComponent>(ent2)->img);
    SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    SDL_RenderFillRect(r,&_game.getWorld()->Get<imageComponent>(ent2)->img.getRect());

    //define actions
    textureManager::imgDir au=library._textureManager->add();
    r=library._textureManager->edit(&au);
    SDL_SetRenderDrawColor(r, 0, 255, 255, 255);
    SDL_RenderFillRect(r,&au.getRect());

    //action animations
    innerAnimation* an=new innerAnimation();
    innerAnimation* an2=new innerAnimation();
    outerAnimation* an3=new outerAnimation();
    an3->addStep(au,10.0, 10);
    an3->addStep(au,10.0, -10);
    an3->addStep(au,10.0, 10);
    an3->addStep(au,10.0, -10);
    an3->addStep(au,10.0, 10);
    an3->addStep(au,10.0, -10);
    an2->addStep(au, 100.0);
    an->addStep(_game.getWorld()->Get<imageComponent>(ent)->img, 100.0);
    an->addStep(au, 500.0);
    an2->addStep(_game.getWorld()->Get<imageComponent>(ent)->img, 1.0);

    //teleport action for the player
    library.aux=new command();
    library.aux->push_back(new innerAnimationCommandComponent(an));
    library.aux->push_back(new outerAnimationCommandComponent(an3));
    library.aux->push_back(new delayCommandComponent(an->getMs()));
    library.aux->push_back(new setCurrentCommandComponent());
    library.aux->push_back(new teleportCommandComponent(10));
    library.aux->push_back(new innerAnimationCommandComponent(an2));
    library.aux->push_back(new delayCommandComponent(an2->getMs()));
    library.aux->push_back(new resetCurrentCommandComponent());
    library.aux->setName("teleport");

    //move action for the npc
    command* rando= new command();
    rando->push_back(new setCurrentCommandComponent());
    rando->push_back(new delayCommandComponent(100));
    rando->push_back(new randomMoveCommandComponent(10));
    rando->push_back(new resetCurrentCommandComponent());
    rando->setName("randomMove");
    rando->stopable=false;
    _game.getWorld()->Assign<posibleActionsComponent>(ent2)->posibilities.push_back(rando->setSource(ent2));

    innerAnimation* an4=new innerAnimation();
    an4->addStep(_game.getWorld()->Get<imageComponent>(ent2)->img, 100.0);
    an4->addStep(au, 500.0);
    an4->addStep(_game.getWorld()->Get<imageComponent>(ent2)->img, 100.0);

    //restore action points action for the npc
    command* recover= new command();
    recover->push_back(new setCurrentCommandComponent());
    recover->push_back(new innerAnimationCommandComponent(an4));
    recover->push_back(new delayCommandComponent(an4->getMs()));
    recover->push_back(new recoverAPCommandComponent(10));
    recover->push_back(new resetCurrentCommandComponent());
    recover->setName("recover");
    recover->stopable=false;
    _game.getWorld()->Get<posibleActionsComponent>(ent2)->posibilities.push_back(recover->setSource(ent2));

    _game.initGame();
    _game.gameLoop();

    //cleaning
    delete library.aux;
    for(auto i:factories)
        delete i;
    delete library._mainWindow;
    delete _game.getWorld();
    return 0;
}
```
This code can be found in the file src/main.cpp

## **How to build**
***
### Install SDL2
```bash
sudo apt-get install libsdl2-dev
```
### Clone the repository
```
git clone git@github.com:Antimateri/DimensionsGame.git
```
### Go to the make folder and build the program
```
cd DimensionsGame/make
make
make clear
```
### Execute the demo main
```
./main
```
