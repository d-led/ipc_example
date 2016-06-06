#include <connection_factory.h>
#include <zmq_factory.h>
#include <nanomsg_factory.h>
#include <os.h>

sink_ptr_t create_sink(std::string const& config) {
    if (os::windows()) {

    } else {

    }
    return sink_ptr_t();
}

source_ptr_t create_source(std::string const& config) {
    if (os::windows()) {

    } else {

    }
    return source_ptr_t();    
}
