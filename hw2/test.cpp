/**
 * Student ID: 403410061
 * Name: Chen, Pi-You
 * Department: Computer Science and Information Engineer
 * Year: 2
 */



/**
 *
 * This code run in lunix environment.
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;

/**
 *
 * Pre: Cross platform solution for clear screen.
 *
 *
 * Post: Print one hundred each times.
 *
 *
 */
void clearscreen()
{
    for(int i=0; i<10; i++)
    {
        cout << "\n\n\n\n\n\n\n\n";
    }
}

/**
 * The class about life.
 * Have some property:
 *      height
 *      width
 *      table with height*width
 * Have some method:
 *      generator: Use patten or random assign.
 *      process: Thoungh rule to update world.
 *      display: Print world in screen.
 */
class GameOfLife
{
public:
    void initialize(int);
    void process(int);
    GameOfLife(int, int);
    void display();
private:
    int height;
    int width;
    int world[256][256];
};


/**
 *
 * To initial height and width about world.
 *
 */

GameOfLife::GameOfLife(int w, int h): width(w),height(h)
{

}


/**
 *
 * Only one argument to decide use which patten or random assign.
 *      1: Glider
 *      2: Lightweight Spaceship
 *      3: Pulsar
 *      4~100: The percent of life cover the world.
 *
 * Give the object's world the patten.
 *
 */


void GameOfLife::initialize(int input)
{
    const int GLIDER[9] =
    {
        1,1,1,
        1,0,0,
        0,1,0
    };
    const int SPACESHIP[20] =
    {
        0,1,0,0,1,
        1,0,0,0,0,
        1,0,0,0,1,
        1,1,1,1,0
    };
    const int PULSAR[13*13] =
    {
        0,0,1,1,0,0,0,0,0,1,1,0,0,
        0,0,0,1,1,0,0,0,1,1,0,0,0,
        1,0,0,1,0,1,0,1,0,1,0,0,1,
        1,1,1,0,1,1,0,1,1,0,1,1,1,
        0,1,0,1,0,1,0,1,0,1,0,1,0,
        0,0,1,1,1,0,0,0,1,1,1,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,1,1,1,0,0,0,1,1,1,0,0,
        0,1,0,1,0,1,0,1,0,1,0,1,0,
        1,1,1,0,1,1,0,1,1,0,1,1,1,
        1,0,0,1,0,1,0,1,0,1,0,0,1,
        0,0,0,1,1,0,0,0,1,1,0,0,0,
        0,0,1,1,0,0,0,0,0,1,1,0,0
    };

    // Check input must between 1~100.
    if(input<0 || input > 100)
    {
        cout << "Please enter 1~100" << endl;
        return ;
    }

    // Decide how many cell need grow.
    int fill = height*width*input/100;
    int prob[256*256];

    for(int i=0; i<fill; i++)
    {
        prob[i] = 1;
    }

    // Random the position of life.
    for(int i=0; i<height*width; i++)
    {
        swap(prob[i],prob[rand()%(height*width - i) + i]);
    }
    int cnt(0);

    // Assign the content to world.
    switch(input)
    {
    case 1:
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(GLIDER[cnt++]==1)
                {
                    world[i+height/2-1][j+width/2-1] = 1;
                }
            }
        }
        break;
    case 2:
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<5; j++)
            {
                if(SPACESHIP[cnt++]==1)
                {
                    world[i+height/2-2][j+width/2-2] = 1;
                }
            }
        }
        break;
    case 3:
        for(int i=0; i<13; i++)
        {
            for(int j=0; j<13; j++)
            {
                if(PULSAR[cnt++]==1)
                {
                    world[i+height/2-6][j+width/2-6] = 1;
                }
            }
        }
        break;
    default:
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                if(prob[cnt++] == 1)
                {
                    world[i][j] = 1;
                }
                else
                {
                    world[i][j] = 0;
                }
            }
        }
    }
}

/**
 *
 * One argument the generation need to process.
 *
 * Let generation to next generation.
 * Work by rule below
 *      1. Dead cell's neighbor have exact three, to live.
 *      2. Live Cell's neighbor between [2,3] , live continue.
 *      3. Live cell's neighbor between [0,1] and [4,8], to dead.
 *
 * Process world by r rounds.
 *
 *
 */

void GameOfLife::process(int r)
{

    const int NEIGHBOR[8][2] = {{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}};

    // Because generation not affect itself, create another to maintain world.
    int next_generation[256][256]= {};


    while(r--)
    {

        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {

                // To record how many neighbor cell had.
                int cnt(0);

                for(int k=0; k<8; k++)
                {
                    int x = i + NEIGHBOR[k][0];
                    int y = j + NEIGHBOR[k][1];
                    if(x>=0 && x<height && y>=0 && y<width && world[x][y]==1)
                        cnt++;
                }

                if(world[i][j] == 1)
                {
                    if(cnt>3 || cnt <= 1)
                        next_generation[i][j] = 0;
                    else
                        next_generation[i][j] = 1;
                }
                else
                {
                    if(cnt==3)
                    {
                        next_generation[i][j] = 1;
                    }
                }

            }
        }

        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                world[i][j] = next_generation[i][j];
            }
        }

    }
}

/**
 *
 * Print world to screen.
 *
 */

void GameOfLife::display()
{
    clearscreen();
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            cout << world[i][j];
        }
        cout << endl;
    }
    cout << endl;

}

/**
 * Test the class.
 *
 * Let user control the option.
 *
 */

int main()
{
    srand(time(NULL));

    int width,height;
    cout << "Please enter the width and height about world (if 0 0 will use default 80 23):";
    cin  >> width >> height;
    if((width>0 && width <16) || (height>0 && height<16) || width>256 || height>256 || width<0 || height<0)
    {
        cout << "width and height must between 16~256." << endl;
        return 0;
    }
    if(width==0 && height==0)
    {
        width = 80;
        height = 23;
    }
    GameOfLife L(width,height);

    int type;
    cout << "Please enter type for initial state (1) (2) (3) more than 4 is %%:";
    cin >> type;

    L.initialize(type);
    L.display();

    int r;
    cout << "Please enter round do you want process:";
    cin >> r;
    if(r<=0)
    {
        cout << "ERROR: round must more than 0.\n";
        return 0;
    }

    int flag;
    cout << "Please enter which way to run? (1 for slow 2 for quick):";
    cin >> flag;

    if(flag<1 && flag>2)
    {
        cout << "ERROR: must enter 1 or 2.\n";
        return 0;
    }

    int diff;
    cout << "Please enter how many process at one time:";
    cin >> diff;

    if(diff<=0)
    {
        cout << "ERROR: must more than 0." << endl;
        return 0;
    }

    int times = r;

    while(r--)
    {
        L.process(diff);
        usleep(100000);//©µ¿ð
        L.display();
        cout << "Generation: " << times-r << "/" << times << endl;
        if(flag==1)
        {
            cout << "\n 1 for continue. Other for take off: ";
            cin >> flag;
        }
    }

    return 0;
}
