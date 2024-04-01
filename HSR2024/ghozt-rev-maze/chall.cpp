#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <bitset>
#include <cstring>
#include "alphabet.h"

// subdermatoglyphic

int maze = 0;

void trace(const char* message) {
    std::cout << message << std::endl;
}

int step(unsigned int x){
    return maze | (1 << (x-65));
}

void a() {
    if(maze != 1445914) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void b() {
    if(maze != 1310720) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void c() {
    if(maze != 18799067) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void d() {
    if(maze != 1310722) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void e() {
    if(maze != 1310730) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void f() {
    if(maze != 67108864) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void g() {
    if(maze != 1986587) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void h() {
    if(maze != 18798683) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void i() {
    if(maze != 18798811) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void j() {
    if(maze != 67108890) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void k() {
    if(maze != 68158874) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void l() {
    if(maze != 1986651) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void m() {
    if(maze != 1441818) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void n() {
    if(maze != 80104932) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}
void o() {
    if(maze != 1970203) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}
void p() {
    if(maze != 18765915) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void q() {
    if(maze != 97106628) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void r() {
    if(maze != 1310746) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void s() {

        if(maze == 0) {
            maze = step(static_cast<int>(__func__[0]));

        }
        else{
            exit(1);
        }
    }

void t() {
    if(maze != 1445915) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void u() {
    if(maze != 262144) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void v() {
    if(maze != 67108864) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void w() {
    if(maze != 72101234) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void x() {
    if(maze != 72104321) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

void y() {
    if(maze != 1988699) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));

    }
}

void z() {
    if(maze != 81103412) {
        exit(1);
    }
    else{
        maze = step(static_cast<int>(__func__[0]));
    }
}

typedef void (*FnPtr)();


int main(int argc,char *argv[]) {

    std::map<std::string, FnPtr> myMap;

    myMap["a"] = a;
    myMap["b"] = b;
    myMap["c"] = c;
    myMap["d"] = d;
    myMap["e"] = e;
    myMap["f"] = f;
    myMap["g"] = g;
    myMap["h"] = h;
    myMap["i"] = i;
    myMap["j"] = j;
    myMap["k"] = k;
    myMap["l"] = l;
    myMap["m"] = m;
    myMap["n"] = n;
    myMap["o"] = o;
    myMap["p"] = p;
    myMap["q"] = q;
    myMap["r"] = r;
    myMap["s"] = s;
    myMap["t"] = t;
    myMap["u"] = u;
    myMap["v"] = v;
    myMap["w"] = w;
    myMap["x"] = x;
    myMap["y"] = y;
    myMap["z"] = z;

    std::string current;
    int l = std::strlen(argv[1]);

    if(l < 17)
    {
        trace("Too short for a flag uh?!");
        exit(1);
    }

    for (int i=0; i < l; i++) {
        current = std::string(1, argv[1][i]);
        myMap[current]();
    }
    trace("Well played ! You can validate with this flag :) Don't forget to add HSR{}");
    return 0;
}
