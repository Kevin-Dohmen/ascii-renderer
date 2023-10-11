#include <iostream>

using namespace std;

struct vec3
{
    float x, y, z;
};

int main(){
    vec3 a = {1., 2., 3.};
    cout << a.x << " " << a.y << " " << a.z << "\n";
    cout << typeid(a).name() << "\n";
}