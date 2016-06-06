#include <zmq_factory.h>

sink_ptr_t create_zmq_sink(std::string const& config);
source_ptr_t create_zmq_source(std::string const& config);
