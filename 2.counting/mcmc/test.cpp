#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

void f(int & b){
    std::cout << "&b : " << &b << std::endl;
}
int main(){
    int a = 0;
    std::cout << "&a : " << &a << std::endl;

    f(a);
}
