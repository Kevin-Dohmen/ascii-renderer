#include <iostream>
#include <cmath>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>

// #ifdef _WIN32
// #include <Windows.h>
// #else
// #include <unistd.h>
// #endif

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class vec2 {
public:
    float x;
    float y;

    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator+(const vec2 &other) const
    {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator-(const vec2 &other) const
    {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator*(float scalar) const
    {
        return vec2(x * scalar, y * scalar);
    }

    vec2 operator/(vec2 scalar) const
    {
        return vec2(x / scalar.x, y / scalar.y);
    }

    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    vec2 normalized() const
    {
        float len = length();
        return vec2(x / len, y / len);
    }

    float dot(const vec2 &other) const
    {
        return x * other.x + y * other.y;
    }

    float cross(const vec2 &other) const
    {
        return x * other.y - y * other.x;
    }
};

class vec3 {
public:
    float x;
    float y;
    float z;

    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3 operator+(const vec3 &other) const
    {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    vec3 operator-(const vec3 &other) const
    {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    vec3 operator*(float scalar) const
    {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    vec3 operator/(float scalar) const
    {
        return vec3(x / scalar, y / scalar, z / scalar);
    }

    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    vec3 normalized() const
    {
        float len = length();
        return vec3(x / len, y / len, z / len);
    }

    float dot(const vec3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    vec3 cross(const vec3 &other) const
    {
        return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
};

vec2 res = vec2(50, 50);

const int gradientlen = 11;
char gradient[gradientlen] = {' ', '.', ':', '-', '~', '=', '+', '*', '#', '%', '@'};

int gettime()
{
    return std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void delay(int milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

float shader(vec2 fragpos, vec2 fragres, float cTime, int cFrame)
{
    vec2 uv = fragpos / fragres;

    float col = 0.f;
    float scale = 10.f;
    float timfact = 1.0f;

    float stime = cTime * 0.001 * timfact;

    col = 0.5 + 0.5 * ((sin(uv.x * scale + stime) + sin(uv.y * scale + stime)) * 0.5);

    // col = uv.length();

    return col;
}

int render(int cFrame, int cTime)
{
    std::string scrn = "";
    for (int y = res.y; y >= 0; y--)
    {
        std::string line = "";
        for (int x = 0; x < res.x; x++)
        {
            float col = shader(vec2(x, y), res, gettime(), cFrame);

            char caracter = gradient[(int)(col * gradientlen)];

            line += char(caracter);
            line += char(caracter);
        }
        scrn += (line + "\n");
    }
    std::cout << scrn;
    return 0;
}

int main()
{
    int tim = gettime();
    int cFrame = 0;
    int prevTime = tim;
    float fps = 0;
    while (true)
    {
        int cTime = gettime();
        render(cFrame, cTime);
        std::cout << "FPS: " << fps << "\n"
                  << "frametime: " << cTime - prevTime << "\n";
        delay(20);
        fps = 1000.0f / (cTime - prevTime);
        cFrame++;
        prevTime = cTime;
    }
    return 0;
}