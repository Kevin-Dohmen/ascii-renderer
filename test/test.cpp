#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>
#include <fstream>

const int resx = 100;
const int resy = 100;
float frame[resx][resy] = {};

const int gradientlen = 10;
char gradient[gradientlen] = {' ', '.', ':', '-', '=', '+', '*', '#', '%', '@'};

int main() {
    char filename[] = "raw_test.data";
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }

    char image[resx * resy];
    file.read(image, resx * resy);

    file.close();

    // Process the image data here
    for (int i = 0; i < resx * resy; i++) {
        int x = i % resx;
        int y = i / resx;
        frame[x][y] = ((((float)image[i] + 256.0f) / 255.0f))*-1.0f+1.0f;
        if(y == 50){
            std::cout << ((((float)image[i] + 256.0f) / 255.0f))*-1.0f+1.0f << " ";
        }
    }
    std::cout << std::endl;

    std::string scrn = "";
    for(int y = 0; y <= resy; y++){
        std::string line = "";
        for(int x = 0; x < resx; x++){
            float col = frame[x][y];

            char caracter = gradient[(int)(col * gradientlen)];

            line += char(caracter);
            line += char(caracter);
        }
        scrn += (line+"\n");
    }
    std::cout << scrn;

    return 0;
}