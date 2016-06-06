#include <os.h>
#include <iostream>
#include <ios>
#include <connection_factory.h>

int main(int argc, char const *argv[]) {
    std::cout << "On windows: " << std::boolalpha << os::windows() << std::endl;

    try {
        const char *connection_string = "ipc:///tmp/reqrep";
        auto source = create_source(connection_string);
        auto sink = create_sink(connection_string);

        std::cout << "Sink is: " << sink->identity() << std::endl;
        std::cout << "Source is: " << source->identity() << std::endl;
        sink->send("hi");
        std::cout<<"received: "<<source->receive()<<std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
