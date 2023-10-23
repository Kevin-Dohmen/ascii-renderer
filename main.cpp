#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class vec2 {
public:
    float x;
    float y;

    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    vec2 operator/(float scalar) const {
        return vec2(x / scalar, y / scalar);
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    vec2 normalized() const {
        float len = length();
        return vec2(x / len, y / len);
    }

    float dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    float cross(const vec2& other) const {
        return x * other.y - y * other.x;
    }
};

class vec3 {
public:
    float x;
    float y;
    float z;

    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    vec3 operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    vec3 operator/(float scalar) const {
        return vec3(x / scalar, y / scalar, z / scalar);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    vec3 normalized() const {
        float len = length();
        return vec3(x / len, y / len, z / len);
    }

    float dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3 cross(const vec3& other) const {
        return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
};

vec2 res = vec2(100, 100);

int gradientlen = 10;
char gradient = " .:-=+*#%@";

int gettime(){
    return std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void delay(int milliseconds){
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

float shader(vec2 fragpos, vec2 fragres, float cTime){
    float col = 0.;
    float scale = 10;
    vec2 uv = fragpos / fragres;
    
    // col = 0.5 + 0.5 * sin(atan((0.5-uvx)/(0.5-uvy)));

    col = 0.5 + 0.5 * ((sin(cTime+uv.x*scale) + sin(cTime+uv.y*scale))/2.);
    return col;
}

int render() {
    std::string scrn = "";
    for x in range(res.y-1, -1, -1):
        std::string linestr = "";
        for y in range(0, res.x):
            
        
}

int main(){
    int tim = gettime();
    int cFrame = 0;
    while(true){
        
        cFrame++;
    }
    return 0;
}