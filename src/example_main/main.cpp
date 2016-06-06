#include <os.h>
#include <iostream>
#include <ios>
#include <connection_factory.h>
#include <nanomsg_factory.h>
#include <chrono>
#include <thread>

void sleep_s(unsigned sec) {
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

int main(int argc, char const *argv[]) {
    std::cout << "On windows: " << std::boolalpha << os::windows() << std::endl;

    try {
        const char *connection_string = "ipc:///tmp/reqrep";
        auto source = create_source(connection_string);
        auto sink = create_sink(connection_string);

        std::cout << "Sink is: " << sink->identity() << std::endl;
        std::cout << "Source is: " << source->identity() << std::endl;
        sink->send("hi");
        std::cout << "received: " << source->receive() << std::endl;
        // disconnect
        source.reset();
        sleep_s(1);
        sink->send("ho");
        sleep_s(1);
        source = create_source(connection_string);
        std::cout << "received after reconnect: " << source->receive() << std::endl;

        const char *n_connection_string = "ipc:///tmp/nreqrep";
        auto n_source = create_nanomsg_source(n_connection_string);
        auto n_sink = create_nanomsg_sink(n_connection_string);
        std::cout << "Sink is: " << n_sink->identity() << std::endl;
        std::cout << "Source is: " << n_source->identity() << std::endl;
        n_sink->send("hi");
        std::cout << "received: " << n_source->receive() << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
