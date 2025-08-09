#include "game.hpp"

Game::Game()
{
    wSize=sf::VideoMode({1600,800});
    window=new sf::RenderWindow(wSize,"Raycaster");
    window->setFramerateLimit(60);

    getMap();
    size.x=(Map.size());
    size.y=(Map[0].size());
    pos.x=size.x/2;pos.y=size.y/2;
    //std::cout<<size.x<<" "<<size.y<<" "<<pos.x<<" "<<pos.y<<std::endl;
}


void Game::getMap()//load file, working
{
    std::ifstream mapFile("map.csv");
    map mapVector;
    std::string tempX,tempY;
    int lineIndex=0;

    while (std::getline(mapFile, tempX)){
        mapVector.push_back(mapLine{});
        std::istringstream tempStream(tempX);

        mapVector[lineIndex].push_back(1);
        while(std::getline(tempStream,tempY,',')){
            mapVector[lineIndex].push_back(std::stoi(tempY));
        }mapVector[lineIndex].push_back(1);

        lineIndex++;
    }
    mapLine line={};
    for (int i=0;i<mapVector.size()+2;i++){line.push_back(1);}
    mapVector.insert(mapVector.begin(),line);
    mapVector.push_back(line);
    Map=scaleMap(mapVector);
    //testing:
    /*for (mapLine x:Map){
        for (int y:x){
            std::cout<<y<<',';
        }std::cout<<'\n';
    }std::exit(0);*/
}

map Game::scaleMap(map mapVector){
    mapLine tempLine(mapVector[0].size()*msr,0);
    map Map(mapVector.size()*msr,tempLine);
    for (int Y=0;Y<mapVector.size();Y++){
        for (int X=0;X<mapVector[Y].size();X++){
            bool node =mapVector[Y][X];
            if (node){
                for (int y=0;y<msr;y++){
                    for (int x=0;x<msr;x++){
                        float yg=(y<hmsr)?std::abs(hmsr-y):y-hmsr;
                        float xg=(x<hmsr)?std::abs(hmsr-x):x-hmsr;
                        int shade=(yg>xg)+1;
                        Map[y+Y*msr][x+X*msr]=shade;
                    }
                }
            }//below code is for adding nodes between blocks
            if (node){
                Map[Y*msr][X*msr]=3;
                Map[Y*msr+msr-1][X*msr]=3;
                Map[Y*msr][X*msr+msr-1]=3;
                Map[Y*msr+msr-1][X*msr+msr-1]=3;
                Map[Y*msr+1][X*msr+1]=3;
                Map[Y*msr+msr-2][X*msr+1]=3;
                Map[Y*msr+1][X*msr+msr-2]=3;
                Map[Y*msr+msr-2][X*msr+msr-2]=3;
            }
        }
    }//below code is for adding nodes between blocks
    /*float node=msr/8;
    for (int Y=0;Y<mapVector.size()-1;Y++){
        for (int X=0;X<mapVector[Y].size()-1;X++){
            if (mapVector[Y][X] || mapVector[Y][X+1] || 
                mapVector[Y+1][X] || mapVector[Y+1][X+1]){
                for (int y=-node/2;y<node/2;y++){
                    for (int x=-node/2;x<node/2;x++){
                        Map[Y*msr+msr+y][X*msr+msr+x]=2;
                    }
                }    
            }
        }
    }*/
    return Map;
}


void Game::main()
{
    if (checkEvent()){return;}
    window->clear(sf::Color::Black);
    display();
    window->display();
}


bool Game::checkEvent()
{
    while (const std::optional<sf::Event> event = window->pollEvent()){
        if (event->is<sf::Event::Closed>()){
            window->close();
            return true;
            break;
        }
    }    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)){
        angle-=2;
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)){
        angle+=2;
    }
    move();
    return false;//returns true and the programm ends
}

void Game::move()
{
    sf::Vector2f orgpos=pos;
    float h=1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)){
        float radians=(90-angle)* (PI / 180);
        float o=std::sin(radians)*h;
        float a=std::cos(radians)*h;
        sf::Vector2f sight(o,a);
        pos+=sight;
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)){
        float radians=(90-angle)* (PI / 180);
        float o=std::sin(radians)*-h;
        float a=std::cos(radians)*-h;
        sf::Vector2f sight(o,a);
        pos+=sight;
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)){
        float radians=(90-angle+90)* (PI / 180);
        float o=std::sin(radians)*h;
        float a=std::cos(radians)*h;
        sf::Vector2f sight(o,a);
        pos+=sight;
    }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)){
        float radians=(90-angle-90)* (PI / 180);
        float o=std::sin(radians)*h;
        float a=std::cos(radians)*h;
        sf::Vector2f sight(o,a);
        pos+=sight;
    }
    if (Map[std::round(pos.x)][std::round(pos.y)]){
        pos=orgpos;
    }
}


void Game::display()
{
    std::vector<sf::RectangleShape> rectangles=tdLoader();
    for (sf::RectangleShape i:rectangles){
        window->draw(i);
    }
    
}


std::vector<sf::RectangleShape> Game::tdLoader()
{
    std::vector<sf::RectangleShape> returns;
    sf::RectangleShape tempRect;

    float rectx=wSize.size.x/range*rate;
    float sight,height,angleStart=angle-range/2;
    int index=0;
    sf::Color color;
    int maxH=wSize.size.y,cubed=size.x/msr*size.y/msr;
    for (float i=0;i<range;i+=rate){
        std::pair<float,int> gcrR=gcr(i+angleStart);//get length of ray
        float dif=i+angleStart-angle;if(dif<0){dif+=360;}if(dif>360){dif-=360;}
        sight=gcrR.first;
        sight=sight*std::cos(dif* (PI / 180));//fix fisheye
        height=(cubed*maxH)/sight/msr;
        //std::cout<<cubed<<" "<<maxH<<" "<<sight<<" "<<height<<"\n";
        if(height>maxH){height=maxH;}
        //height of what the ray sees based on the length of sight
        tempRect.setSize(sf::Vector2f(rectx, height));//create rectangle
        tempRect.setPosition({index*rectx,(wSize.size.y-height)/2});
        switch(gcrR.second){
            case 1:color=sf::Color(150,0,0);break;
            case 2:color=sf::Color(250,50,50);break;
        }tempRect.setFillColor(color);
        returns.push_back(tempRect);
        index++;
    }
    return returns;

}


std::pair<float,int> Game::gcr(float rayAngle)
{
    float radians=(90-rayAngle)* (PI / 180);
    for (float h=0;;h+=0.05){
        float o=std::sin(radians)*h;
        float a=std::cos(radians)*h;
        sf::Vector2f sight(o,a);
        sight+=pos;
        int spot=Map[int(std::round(sight.x))][int(std::round(sight.y))];
        if (spot){
            std::pair<float,int> returns;
            returns.first=h;
            returns.second=spot;
            return returns;
        }
    }
}