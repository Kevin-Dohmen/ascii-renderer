#include <iostream>
#include <cmath>
#include <thread>
#include <fstream>

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

    vec2 operator*(vec2 scalar) const
    {
        return vec2(x * scalar.x, y * scalar.y);
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

const int resx = 500;
const int resy = 500;
const int colamnt = 3;
const vec2 resolution = vec2(resx, resy);

int writefile(float image[resx][resy][colamnt]) {
    std::ofstream file;
    file.open("image.data");
    for (int y = 0; y < resy; y++) {
        for (int x = 0; x < resx; x++) {
            for (int c = 0; c < colamnt; c++){
                // std::cout << x << " " << y << " " << c << std::endl;
                float val = image[x][y][c];
                if(val >= 0.0f && val <= 1.0f){
                    file << (int8_t)(val*256.0f);
                } else {
                    file << (int8_t)0;
                }
            }
        }
    }
    file.close();
    return 0;
}

vec3 shader(vec2 fragres, vec2 fragpos){
    vec3 col = vec3(0.0f, 0.0f, 0.0f);
    vec2 uv = (fragpos / fragres);
    col.x = uv.x;
    col.y = uv.y;
    col.z = uv.length();
    // std::cout << col.y << std::endl;
    // std::cout << uv.x << " " << uv.y << " " << uv.length() << std::endl;
    return col;
}
 
int main() {
    float image[resx][resy][colamnt];
    for(int x = 0; x < resx; x++){
        for(int y = 0; y < resy; y++){
            vec3 col = shader(resolution, vec2(x, y));
            image[x][y][0] = col.x;
            image[x][y][1] = col.y;
            image[x][y][2] = col.z;
        }
    }

    writefile(image);
    return 0;
}
