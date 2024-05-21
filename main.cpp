#include <iostream>
#include <conio.h>
using namespace std;

// the e is to denote enum
enum eDir { 
    STOP = 0, 
    LEFT = 1, 
    UPLEFT = 2, 
    DOWNLEFT = 3, 
    RIGHT = 4,
    UPRIGHT = 5,
    DOWNRIGHT = 6
};
class cBall {
    private:
        int x, y;
        int initX, initY;
        eDir currDir;
    public:
    // constructor to initialize position of ball and set its direction to STOP
    // equivalent to Java constructor
    cBall(int posX, int posY) {
        initX = posX;
        initY = posY;
        x = posX; 
        y = posY;
        currDir = STOP;
    }
    void reset() {
        x = initX;
        y = initY;
        currDir = STOP;
    }
    // Java setter essentially
    void changeDir(eDir d) {
        currDir = d;
    }
    void randomDir() {
        // typecast to eDir for enum
        currDir = (eDir)((rand() % 6) + 1);
    }
    // inline because they are small functions
    // const member function since getters don't modify 
    inline int getX() const { return x; }
    inline int getY() const { return y; }
    inline eDir getDir() const {return currDir;}
    void movePos() {
        // check self currDir upon calling movePos
        switch (currDir) {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--;
                y--;
                break;
            case DOWNLEFT:
                x--; 
                y++;
                break;
            case UPRIGHT:
                x++; 
                y--;
                break;
            case DOWNRIGHT:
                x++; 
                y++;
                break;
            default:
                break;
        }
    }
    // friend allows the function to access both private and public parts of class cBall
    // overload bit shift left operator
    // this is essentially just overriding bit shift left to instead output to cout
    // but with more "privileges" than usual
    // and use reference to const to avoid copying cBall
    // essentially, the equivalent of overriding print function in Python.
    friend ostream & operator<<(ostream& o, const cBall& c){
        o << "Ball [" << c.x << "," << c.y << "][" << c.currDir << "]";
        return o;
    }
};
class cPaddle {
    private:
        int x, y;
        int initX, initY;
    public:
        // default constructor
        cPaddle() {
            x = y = 0;
        }
        // constructor delegation, to avoid doubling construction?
        cPaddle(int posX, int posY) : cPaddle() {
            initX = posX;
            initY = posY;
            x = posX;
            y = posY;
        }
        inline void reset() {x = initX; y = initY; }
        inline int getX() const { return x; }
        inline int getY() const { return y; }
        inline void moveUp() { y--; }
        inline void moveDown() { y++; }
        friend ostream & operator<<(ostream& o, const cPaddle& c){
            o << "Paddle [" << c.x << "," << c.y << "]";
            return o;
        }        
};
class cGameManager {
    private:
        int width, height;
        int score1, score2;
        char up1, down1, up2, down2;
        bool quit;
        // possibly null, since this is the game manager.
        cBall *ball;
        cPaddle *player1;
        cPaddle *player2;
    public:
     cGameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        // keypress map
        up1 = 'w'; up2 = 'i';
        down1 = 's'; down2 = 'k';
        score1 = score2 = 0;
        width = w; height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }
    // define destructor, to be called when gameManager stops being used
    ~cGameManager() {
        delete ball, player1, player2;
    }
    void scoreUp(cPaddle *player)
    {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;
        // we use -> because ball, player1, player2 are pointers
        // so -> acccesses the respective resets
        // ball.reset() would only be valid on an actual object e.g. a cBall ball
        ball->reset();
        player1->reset();
        player2->reset();
    }
    // the renderer. straightforward implementation.
    void draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;
 
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();
 
                if (j == 0)
                    cout << "\xB2";
 
                if (ballx == j && bally == i)
                    cout << "O"; //ball
                else if (player1x == j && player1y == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y == i)
                    cout << "\xDB"; //player2
 
                else if (player1x == j && player1y + 1 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 2 == i)
                    cout << "\xDB"; //player1
                else if (player1x == j && player1y + 3 == i)
                    cout << "\xDB"; //player1
 
                else if (player2x == j && player2y + 1 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 2 == i)
                    cout << "\xDB"; //player1
                else if (player2x == j && player2y + 3 == i)
                    cout << "\xDB"; //player1
                else
                    cout << " ";
 
                if (j == width - 1)
                    cout << "\xB2";
            }
            cout << endl;
        }
 
        for (int i = 0; i < width + 2; i++)
            cout << "\xB2";
        cout << endl;
 
        cout << "Score 1: " << score1 << endl << "Score 2: " << score2 << endl;
    }
    void input() {
        ball->movePos();
 
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();
 
        // unfortunately current implementation restricts this to Windows API
        // by using conio.h
        // checks for keyboard hit
        if (_kbhit())
        {
            // returns currently pressed key's value
            char keyVal = _getch();
            if (keyVal == up1)
                if (player1y > 0)
                    player1->moveUp();
            if (keyVal == up2)
                if (player2y > 0)
                    player2->moveUp();
            if (keyVal == down1)
                if (player1y + 4 < height)
                    player1->moveDown();
            if (keyVal == down2)
                if (player2y + 4 < height)
                    player2->moveDown();
 
            if (ball->getDir() == STOP)
                ball->randomDir();
 
            if (keyVal == 'q')
                quit = true;
        }
    }
    void logic() {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();
 
        //left paddle
        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1)
                if (bally == player1y + i)
                    ball->changeDir((eDir)((rand() % 3) + 4));
 
        //right paddle
        for (int i = 0; i < 4; i++)
            if (ballx == player2x - 1)
                if (bally == player2y + i)
                    ball->changeDir((eDir)((rand() % 3) + 1));
 
        //bottom wall
        if (bally == height - 1)
            ball->changeDir(ball->getDir() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        //top wall
        if (bally == 0)
            ball->changeDir(ball->getDir() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        //right wall
        if (ballx == width - 1)
            scoreUp(player1);
        //left wall
        if (ballx == 0)
            scoreUp(player2);        
    }
    void run()
    {
        while (!quit)
        {
            draw();
            input();
            logic();
        }
    }   
};
int main() {
    cGameManager c(40, 20);
    c.run();
    return 0;
}