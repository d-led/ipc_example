#include <connection_factory.h>
#include <zmq_factory.h>
#include <nanomsg_factory.h>
#include <os.h>

sink_ptr_t create_sink(std::string const& config) {
    if (os::windows()) {
        return create_nanomsg_sink(config);
    } else {
        return create_zmq_sink(config);
    }
}

source_ptr_t create_source(std::string const& config) {
    if (os::windows()) {
        return create_nanomsg_source(config);
    } else {
        return create_zmq_source(config);
    }
}
