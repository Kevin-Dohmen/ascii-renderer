#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
// #include <sys/time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

const int xres = 100;
const int yres = 100;

float scrn[xres][yres];

const int gradientamnt = 15;
char gradient[gradientamnt] = {' ', '.', ',', ':', ';', '*', 'o', '&', '#', '@', '$', 'Q', 'M', 'B', 'K'};

int gettime(){
    return std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void delay(int milliseconds){
    //windows:
    //Sleep(milliseconds);

    //Unix:
    // usleep(milliseconds*1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
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
            float scale = 10;
            
            // col = 0.5 + 0.5 * sin(atan((0.5-uvx)/(0.5-uvy)));

            col = 0.5 + 0.5 * ((sin(cTime+uvx*scale) + sin(cTime+uvy*scale))/2.);

            scrn[xpos][ypos] = float(col);
        }
    }

    // render
    std::string framestr = "";
    for(int y = yres-1; y >= 0; y--){
        std::string linestr = "";
        for(int x = 0; x < xres; x++){
            float bwval = scrn[x][y];
            float pix = 0.;
            pix = bwval;
            if(bwval >= 0. && bwval <= 1.){
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
    std::cout << framestr;
    std::cout << "\n";
    return 0;
}

int main(){
    int sTime = gettime();
    int cTime;
    for(int l = 0; l < 50000; l++){
        int t = gettime();
        cTime = t - sTime;

        frame(cTime, l);

        delay(50);
    }
    int eTime = gettime();

    std::cout << sTime;
    std::cout << "\n";
    std::cout << cTime;
    std::cout << "\n";
    std::cout << eTime;
    std::cout << "\n";
    std::cout << eTime - sTime;
    std::cout << "\n";
    return 0;
}
