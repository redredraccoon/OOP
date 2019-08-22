/*
Student ID:404410089
Name:Liao yi_ping
Dept:Computer Science and Information Engineering
Year:2
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
/*
Preconditions:class about gameoflife
Postconditions:have public member function:
                *initialize:initialize the world
                *proceed:play the generation
                *display:show the result
               have private member variable:
                *world's wide and height
                *world

*/
class GameOfLife
{
public:
    void initialize(int);
    void proceed(int);
    void display();
    GameOfLife(int,int);
private:
    int wide;
    int height;
    int world[256][256];
};
/*
Preconditions:wide & height of the world
Postconditions:initialize the wide & height of the world
*/
GameOfLife::GameOfLife(int w,int h):wide(w),height(h)
{

}
/*
Preconditions:input represents which pattern user chooses
Postconditions:take the selected pattern into the world
*/
void GameOfLife::initialize(int input)
{
    if(input < 1 || input > 100)
    {
        cout << "please input an integer from 1 to 100, try again~\n";
        return;
    }

    for(int i=0; i < 256; i++)
        for(int j=0; j < 256; j++)
            world[i][j]=0;

    const int Glider[3 * 3]= {1,1,1,
                              1,0,0,
                              0,1,0
                             };
    const int LightweightSpaceship[5 * 4]= {0,1,0,0,1,
                                            1,0,0,0,0,
                                            1,0,0,0,1,
                                            1,1,1,1,0
                                           };
    const int Pulsar[13 * 13]= {0,0,1,1,0,0,0,0,0,1,1,0,0,
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
    int bit=0;
    switch(input)
    {
    case 1:
        for(int i=0; i < 3; i++)
            for(int j=0; j < 3; j++)
            {
                if(Glider[bit++]==1) world[i + height/2 -1][j + wide/2 -1]=1;
            }
        break;
    case 2:
        for(int i=0; i < 4; i++)
            for(int j=0; j < 5; j++)
            {
                if(LightweightSpaceship[bit++]==1) world[i + height/2 -2][j + wide/2 -2]=1;
            }
        break;
    case 3:
        for(int i=0; i < 13; i++)
            for(int j=0; j < 13; j++)
            {
                if(Pulsar[bit++]==1) world[i + height/2 -6][j + wide/2 -6]=1;
            }
        break;
    default:
        //the number of life cell
        int stuff = wide * height * input / 100;
        //the model matrix
        int prob[256 * 256];
        int pos,tmp;

        for(int i=0; i < stuff; i++)prob[i] = 1;

        unsigned seed;
        seed = (unsigned)time(NULL);
        srand(seed);

        // Random the position of life.
        for(int i=height * wide - 1; i > 0; i--)
        {
            //choose randomly from 0 to i
            pos = (int)(rand() / (RAND_MAX + 1.0) * (i + 1));
            //exchange two number
            tmp = prob[pos];
            prob[pos] = prob[i];
            prob[i]=tmp;
        }
        //substitute the model matrix into the world
        for(int i=0; i<height; i++)
            for(int j=0; j<wide; j++)
            {
                if(prob[bit++] == 1)world[i][j] = 1;
                else world[i][j] = 0;
            }
    }
}
/*
Preconditions:r represents the number of generation user want to proceed at once
Postconditions:generate the new world according to the rules
*/
void GameOfLife::proceed(int r)
{
    int next_generation[256][256]= {};
    while(r--)
    {
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<wide; j++)
            {
                int count = 0;//number of life cells around the cell
                for ( int k = i-1; k <= i + 1; k++ )
                {
                    for ( int h = j-1; h <= j+1; h++ )
                    {
                        if ( k == i && h == j )continue;
                        if ( k > -1 && k < height && h > -1 && h < wide && world[k][h] == 1)count++;
                    }
                }
                //cell dies
                if(count < 2 || count > 3)
                    next_generation[i][j] = 0;
                //cell stays at the same situation
                if(count == 2)
                    next_generation[i][j] = world[i][j];
                //cell stays alive, or birth
                if(count == 3)
                    next_generation[i][j] = 1;
            }
        }
    }
    //substitute the new world into world
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<wide; j++)
        {
            world[i][j] = next_generation[i][j];
        }
    }
}
/*
Preconditions:show the world
Postconditions:show the world
*/
void GameOfLife::display()
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<wide; j++)
        {
            if(world[i][j]==1) cout << "*";
            else cout << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{

    while(1)
    {
        cout << "--------------------------------------------------" << "\n";
        cout << "\n" << "Input the wide and height of the world," << "\n";
        cout << "you must input the number between 16 and 256." << "\n";
        cout << "If you input 0 0, it will default 80 30" << "\n";
        int wide,height;
        cin >> wide >> height;
        if((wide < 16 || wide > 256 || height < 16 || height > 256) && (wide != 0 || height != 0))
        {
            cout << "You should input the number between 16 and 256!!!" << "\n";
            cout << "Try again~" << "\n";
            continue;
        }
        if(wide == 0 && height == 0)
        {
            wide=80;
            height=23;
        }
        GameOfLife Act(wide,height);

        cout << "Input which pattern you want to act 1(Glider), 2(LightweightSpaceship), 3(Pulsar), 4~100 represent % : ";
        int pattern;
        cin >> pattern;
        Act.initialize(pattern);
        Act.display();

        cout << "Input how many rounds you want to run : ";
        int round;
        cin >> round;

        cout << "Input how fast you want to run, 1(step by step), 2(fast): ";
        int speed;
        cin >> speed;

        int time=0;
        if(speed == 1)
        {
            while(round--)
            {
                Act.proceed(1);
                Act.display();
                time++;
                cout << "Have been passed " << time << " generations." << "\n";
                if(speed == 1)
                {
                    cout << "\n" << "Input 1 to continue, or input other to stop : ";
                    cin >> speed;
                    if(speed != 1) break;
                }
            }
        }
        else
        {
            cout << "Input how many processes you want to proceed each time: ";
            int pss;
            cin >> pss;

            for(int i=round; i > 0; i-=pss)
            {
                system("CLS");//clear the screen
                Act.proceed(pss);
                Act.display();
                time+=pss;
            }
        }
    }
}
