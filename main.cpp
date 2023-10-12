#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>
#include <vector>
// #include <sys/time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

const int xres = 100;
const int yres = 100;

float scrn[xres][yres];

const int gradientamnt = 12;
char gradient[gradientamnt] = {' ', '.', ':', ';', '~', '+', '*', '=', 'x', 'X', '$', '&'};

int gettime(){
    return duration_cast<milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

void delay(int milliseconds){
    //windows:
    //Sleep(milliseconds);

    //Unix:
    usleep(milliseconds*1000);
}

int frame(int tim, int cFrame){
    for(int ypos = 0; ypos < yres; ypos++){
        // frame constants
        float iResX = float(xres);
        float iResY = float(yres);
        float cTime = tim / 1000.;

        // shader
        for(int xpos = 0; xpos < xres; xpos++){
            float iPosX = float(xpos);
            float iPosY = float(ypos);
            float uvx = iPosX/iResX;
            float uvy = iPosY/iResY;

            float col = 0.;
            float scale = 15.;
            
            col = 0.5 + 0.5 * ((sin(cTime+uvx*scale) + sin(cTime+uvy*scale))/2.);


            scrn[xpos][ypos] = float(col);
        }
    }

    // render
    string framestr = "";
    for(int y = yres-1; y >= 0; y--){
        string linestr = "";
        for(int x = 0; x < xres; x++){
            float bwval = scrn[x][y];
            float pix = 0.;
            pix = bwval;
            if(0. <= bwval <= 1.){
                pix = bwval;
            }
            else if(bwval < 0.){
                pix = 0.;
            }
            else{
                pix = 1.;
            }
            // cout << gradient[int(floor(pix*(gradientamnt-1)))];
            // cout << gradient[int(floor(pix*(gradientamnt-1)))];
            linestr = linestr + gradient[int(floor(pix*(gradientamnt-1)))] + gradient[int(floor(pix*(gradientamnt-1)))];
        }
        //cout << linestr;
        //cout << "\n";
        framestr = framestr + linestr + "\n";
    }
    cout << framestr;
    cout << "\n";
    return 0;
}

int main(){
    int sTime = gettime();
    int cTime;
    for(int l = 0; l < 5000; l++){
        int t = gettime();
        cTime = t - sTime;

        frame(cTime, l);

        delay(50);
    }
    int eTime = gettime();

    cout << sTime;
    cout << "\n";
    cout << cTime;
    cout << "\n";
    cout << eTime;
    cout << "\n";
    cout << eTime - sTime;
    cout << "\n";
    return 0;
}
