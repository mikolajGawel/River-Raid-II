//Mikołaj Gaweł-Kucab
//River Raid II
//10.10.2021

// zaimplementowanie plików nagłówkowych bibliotek do programu
#include <raylib.h>
#include <random>
#include <time.h>
#include <iostream>
//statusy gry
enum game_status
{
    MENU,IN_GAME,GAME_OVER
};
#define WIDTH 800 //szerokość okna
#define HEIGHT 600 //wysokość okna
//szybkość gracza
#define PLAYER_SPEED 5
//szybkość pocisku
#define PROJECTILE_SPEED 20
//klasa mapy gry
class Map
{
    public:
    Texture lm,rm;//lewa część mapy,prawa
    int lmx,rmx,lmy,rmy;//współrzędnę częsci mapy

    Texture lm2,rm2;//lewa część mapy2,prawa
    int lmx2,rmx2,lmy2,rmy2;//współrzędnę częsci mapy2

    Map()
    {
        lm = LoadTexture("rsc/left.png");
        rm = LoadTexture("rsc/right.png");
        lm.width = 100;rm.width = 100;
        lm.height = HEIGHT;rm.height = HEIGHT;
        lmx = 0;rmx = WIDTH-rm.width;lmy = 0;rmy = 0;

        lm2 = LoadTexture("rsc/left.png");
        rm2 = LoadTexture("rsc/right.png");
        lm2.width = 100;rm2.width = 100;
        lm2.height = HEIGHT;rm2.height = HEIGHT;
        lmx2 = 0;rmx2 = WIDTH-rm2.width;
        lmy2 = 0-lm2.height;rmy2 = 0-rm2.height;
    }
    ~Map()
    {
        UnloadTexture(lm);
        UnloadTexture(rm);
    }
    void updtateMap()
    {
        lmy+=PLAYER_SPEED;
        rmy+=PLAYER_SPEED;
        lmy2+=PLAYER_SPEED;
        rmy2+=PLAYER_SPEED;
        if(lmy > HEIGHT){lmy = 10-lm.height;}
        if(lmy2 > HEIGHT){lmy2 = 10-lm2.height;}
        if(rmy2 > HEIGHT){rmy2 = 10-rm2.height;}
        if(rmy > HEIGHT){rmy = 10-rm.height;}
    }
    void drawMap()
    {
        DrawTexture(lm,lmx,lmy,WHITE);
        DrawTexture(rm,rmx,rmy,WHITE);

        DrawTexture(lm2,lmx2,lmy2,WHITE);
        DrawTexture(rm2,rmx2,rmy2,WHITE);
    }
};
//klasa helikoptera
class Helicopter
{
    public:
    int num;//numer helikotera w tabeli
    Texture2D tex;
    Texture2D destroyed;
    bool right;
    bool exist = true;//czy obiekt instnieje
    int x,y,w,h;//pozycja ,szerokość i wysokość
    
    Helicopter(int x,int y)
    {
        tex= LoadTexture("rsc/helicopter.png");
        destroyed = LoadTexture("rsc/destroyed.png");
        tex.width = 100;tex.height = 100;
        w = -tex.width;
        h = tex.height;
        this->x = x;this->y = y;
        int ra = rand()%2;
        ra == 0? right = true : right = false;
    } Helicopter()
    {
        tex= LoadTexture("rsc/helicopter.png");
        tex.width = 100;tex.height = 100;
        w = tex.width;
        h = tex.height;
        int ra = rand()%2;
        ra == 0? right = true : right = false;
        
    }
    ~Helicopter()
    {UnloadTexture(tex);}
    void setHelicopter(int posX,int posY)//ustawia helikopter 
    {
        exist = true;
        x = posX;y = posY;
    }
    void draw()
    {
      if(exist){  DrawTexture(tex,x,y,WHITE);}
    }
    void update()
    {
      if(exist){  y+=PLAYER_SPEED;}
        
    }

};
//klasa łodzi (właściwie prawie taka sama jak helikopter)
class Boat
{
    public:
    int num;//numer helikotera w tabeli
    Texture2D tex;
 
    bool right;
    bool exist = true;//czy obiekt instnieje
    int x,y,w,h;//pozycja ,szerokość i wysokość
    
    Boat()
    {
        tex= LoadTexture("rsc/boat.png");
        tex.width = 240/10*8;tex.height = 120/10*8;
        w = tex.width;
        h = tex.height;
        int ra = rand()%2;
        ra == 0? right = true : right = false;
        
    }
    ~Boat()
    {UnloadTexture(tex);}
    void setBoat(int posX,int posY)//ustawia helikopter 
    {
        exist = true;
        x = posX;y = posY;
    }
    void draw()
    {
      if(exist){  DrawTexture(tex,x,y,WHITE);}
    }
    void update()
    {
      if(exist){  y+=PLAYER_SPEED;}
        
    }

};
//klasa samolotu
class Plane
{
    Texture2D player;
    Texture2D destroyed;
    public:
    int x,y,width,height;
    ~Plane()
    {UnloadTexture(player);UnloadTexture(destroyed);}
    
    Plane(int x,int y,int width ,int height)
    {
        this->x = x;this->y = y;
        this->width = width;
        this->height = height;
        player = LoadTexture("rsc/plane.png");
        destroyed = LoadTexture("rsc/destroyed.png");
        player.width = width;
        player.height = height;
         destroyed.width = width;
        destroyed.height = height;
    }
    void update()
    {
        
        if(IsKeyDown(KEY_W))
        {
            y-=PLAYER_SPEED;
        }
        if(IsKeyDown(KEY_S))
        {
            y+=PLAYER_SPEED;
        }  
        if(IsKeyDown(KEY_A))
        {
            x-=PLAYER_SPEED;
        }
        if(IsKeyDown(KEY_D))
        {
            x+=PLAYER_SPEED;
        }

    }
    void draw()
    {
        DrawTexture(player,x,y,YELLOW);
    }
    void drawDestroyed()
    {
        DrawTexture(destroyed,x,y,WHITE);
    }
};
//klasa pocisku
class Projectile
{
    public:
    int x = -879878,y = -79798,w = 10,h = 30;
    bool created = false;
    void shot(int x,int y)
    {
        this->x = x;
        this->y = y;
        created = true;
    }
    void update()
    {
        if(created)
        {
            if(y+h < 0)
            {
                created = false;
            }
            y-=PROJECTILE_SPEED;
        }
    }
    void draw()
    {
        if(created){DrawRectangle(x,y,w,h,YELLOW);}
    }
};
//generuje losową pozycję dla przeszkody w zakresie 100-600
int helicopterRandomPosition()
{
    int r = rand()%(WIDTH-100-100);
    if(r<100){r+=100;}
    return r;
}int boatRandomPosition()
{
    int r = rand()%(WIDTH-100-280);
    if(r<100){r+=100;}
    return r;
}
//start programu
int main()
{
    int best_score = 0;
    int score = 0;

    bool debug = false;
    int status =  MENU;
    srand(time(NULL));
    InitWindow(WIDTH,HEIGHT,"River Raid II Mikołaj Gaweł-Kucab");
    InitAudioDevice();
    SetTargetFPS(60);
    
    Sound shot = LoadSound("rsc/shoot.wav");

    Plane player(0,0,100,100);
    Projectile p[10];
    player.x = (WIDTH-player.width)/2;player.y = HEIGHT/2;
    Map m;
    Helicopter h[3];
    Boat b[3];
    int lastProjectile = 0;
    for(int i = 1;i <= 3;i++)
    {  
        h[i-1].setHelicopter(helicopterRandomPosition(),i*-200);
    }for(int i = 1;i <= 3;i++)
    {  
        b[i-1].setBoat(boatRandomPosition(),i*-200);
    }
    while(!WindowShouldClose())
    {
       if(IsKeyReleased(KEY_ZERO))
       {
            debug = true;
       }
       
        
        BeginDrawing();
        if(status == IN_GAME)
        { 
            //sprawdzanie czy gracz dodknął ściany bocznej
            if(CheckCollisionRecs((Rectangle){(float)player.x,(float)player.y,(float)player.width,(float)player.height},(Rectangle){(float)m.lmx,(float)m.lmy,100.0f,(float)HEIGHT}) == true)
            {status = GAME_OVER;}
            if(CheckCollisionRecs((Rectangle){(float)player.x,(float)player.y,(float)player.width,(float)player.height},(Rectangle){(float)m.lmx2,(float)m.lmy2,100.0f,(float)HEIGHT}) == true)
            {status = GAME_OVER;}
            if(CheckCollisionRecs((Rectangle){(float)player.x,(float)player.y,(float)player.width,(float)player.height},(Rectangle){(float)m.rmx,(float)m.rmy,100.0f,(float)HEIGHT}) == true)
            {status = GAME_OVER;}
            if(CheckCollisionRecs((Rectangle){(float)player.x,(float)player.y,(float)player.width,(float)player.height},(Rectangle){(float)m.rmx2,(float)m.rmy2,100.0f,(float)HEIGHT}) == true)
            {status = GAME_OVER;}
       
            //sprawdzenie czy gracz jest poza mapą
            if(player.y > HEIGHT/6*5 || player.y+player.height < 0)
            {
                status = GAME_OVER;
            }
            //sprawdzenie czy gracz dotyka helikopterów
            for(int i = 0;i < 3;i++)
            {
                if(CheckCollisionRecs((Rectangle){(float)h[i].x,(float)h[i].y,(float)h[i].w,(float)h[i].h},(Rectangle){(float)player.x,(float)player.y,(float)player.width,(float)player.height}))
                {status = GAME_OVER;} 
            }  for(int i = 0;i < 3;i++)
            {
                if(CheckCollisionRecs((Rectangle){(float)b[i].x,(float)b[i].y,(float)b[i].w,(float)b[i].h},(Rectangle){(float)player.x,(float)player.y,(float)player.width,(float)player.height}))
                {status = GAME_OVER;} 
            }
            //sprawdzenie czy pocisk w coś trafił
            for(int i = 0;i < 3;i++)
            {
                for(int j = 0;j < 10;j++)
                {
                    if(CheckCollisionRecs((Rectangle){(float)p[j].x,(float)p[j].y,10.0f,30.0f},(Rectangle){(float)h[i].x,(float)h[i].y,(float)h[i].w,(float)h[i].h}) == true)
                    {
                        p[j].created = false;
                        p[j].x = -8768687;//byle jak najdalej z tąd
                        h[i].setHelicopter(helicopterRandomPosition(),-200);
                        score+=10;
                    }
                }
            }   
            for(int i = 0;i < 3;i++)
            {
                for(int j = 0;j < 10;j++)
                {
                  
                    if(CheckCollisionRecs((Rectangle){(float)p[j].x,(float)p[j].y,10.0f,30.0f},(Rectangle){(float)b[i].x,(float)b[i].y,(float)b[i].w,(float)b[i].h}) == true)
                    {
                        p[j].created = false;
                        p[j].x = -8768687;//byle jak najdalej z tąd
                        b[i].setBoat(boatRandomPosition(),-200);
                        score+=5;
                    }
                }
            }
            for(int i = 0;i < 10;i++)
            {
                if(p[i].y < 5)
                {
                    p[i].x = -87987;
                }
            }
            if(lastProjectile >= 10)lastProjectile = 0;
            if(IsKeyReleased(KEY_SPACE))
            {
                p[lastProjectile].shot(player.x+player.width/2-10,player.y+player.height/3*2);
                lastProjectile++;
               // PlaySound(shot);
            }
            ClearBackground(DARKBLUE);
            m.drawMap();
            m.updtateMap();
            
            player.draw();
            player.update();
           
            for(int i = 0;i < 3;i++)
            {
                h[i].draw();h[i].update();
                if(h[i].y > HEIGHT)
                {
                    std::cout << "Helicopter been destroyed\n";h[i].setHelicopter(helicopterRandomPosition(),-200);
                }
            }for(int i = 0;i < 3;i++)
            {
                b[i].draw();b[i].update();
                if(b[i].y > HEIGHT)
                {
                    std::cout << "Boat been destroyed\n";b[i].setBoat(boatRandomPosition(),-200);
                }
            }
            for(int i = 0;i< 10;i++)
            {
                p[i].update();
                p[i].draw();
            }

            DrawRectangle(0,HEIGHT/6*5,WIDTH,HEIGHT/5,BLACK);
            DrawText(TextFormat("Wynik %i",score),100,HEIGHT/6*5,18,WHITE);

            if(debug)
            { 
                DrawText(FormatText("FPS:%i",GetFPS()),0,0,20,YELLOW);
                DrawText(FormatText("Projectile:%i",lastProjectile),0,50,20,YELLOW);
                DrawText(FormatText("X:%i",player.x),0,100,20,YELLOW);
                DrawText(FormatText("Y:%i",player.y),0,150,20,YELLOW);
            }
        }else if(status == GAME_OVER)
        {
            m.drawMap();
          
         
            player.drawDestroyed();
            DrawRectangle(0,HEIGHT/6*5,WIDTH,HEIGHT/5,BLACK);
            DrawText(FormatText("!Koniec Gry \nkliknij spacje aby zagrac ponownie/n Wynik: %i",score),100,HEIGHT/6*5,18,WHITE);

            if(debug)
            { 
                DrawText(FormatText("FPS:%i",GetFPS()),0,0,20,YELLOW);
                DrawText(FormatText("Projectile:%i",lastProjectile),0,50,20,YELLOW);
                DrawText(FormatText("X:%i",player.x),0,100,20,YELLOW);
                DrawText(FormatText("Y:%i",player.y),0,150,20,YELLOW);
            }
            if(IsKeyReleased(KEY_SPACE))
            {
                player.x = (WIDTH-player.width)/2;player.y = HEIGHT/2;
                score = 0;
                m.lmy = 0;
                m.rmy = 0;
                m.lmy2 = -m.lm2.height;
                m.rmy2 = -m.rm2.height;
                for(int i = 1;i <= 3;i++)
                {
                    h[i-1].setHelicopter(helicopterRandomPosition(),i*-200);
                }

                for(int i = 1;i <= 3;i++)
                {
                    b[i-1].setBoat(boatRandomPosition(),i*-200);
                }
                status = IN_GAME;
            }
        }else if(status == MENU)
        {
            for(int i = 0;i < 10;i++){p[i].x = -78087;}
            m.drawMap();
            ClearBackground(DARKBLUE);
            player.draw();
            if(best_score < score)score = best_score;
            score = 0;
            DrawRectangle(0,HEIGHT/6*5,WIDTH,HEIGHT/5,BLACK);
            DrawText(
                "River Raid II                                                      Mikolaj Gawel-Kucab\nkliknij [spacje] aby zagrac                                                      @2021",100,HEIGHT/6*5,18,WHITE);
        
            if(IsKeyReleased(KEY_SPACE))
            {
                player.x = (WIDTH-player.width)/2;player.y = HEIGHT/2;
              
                m.lmy = 0;
                m.rmy = 0;
                m.lmy2 = -m.lm2.height;
                m.rmy2 = -m.rm2.height;
                for(int i = 1;i <= 3;i++)
                {
                    h[i-1].setHelicopter(helicopterRandomPosition(),i*-200);
                }
                 for(int i = 1;i <= 3;i++)
                {
                    b[i-1].setBoat(boatRandomPosition(),i*-200);
                }
                status = IN_GAME;
            }
           if(debug)
            { 
                DrawText(FormatText("FPS:%i",GetFPS()),0,0,20,YELLOW);
                DrawText(FormatText("X:%i",player.x),0,100,20,YELLOW);
                DrawText(FormatText("Y:%i",player.y),0,150,20,YELLOW);
            }
            
        }

        EndDrawing();
    }
    UnloadSound(shot);
    CloseAudioDevice();
    CloseWindow();
}
