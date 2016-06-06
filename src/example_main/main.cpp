#include <os.h>
#include <iostream>
#include <ios>

int main(int argc, char const *argv[]) {
    std::cout << "On windows: " << std::boolalpha << os::windows() << std::endl;
    return 0;
}
