#include <zmq_factory.h>
#include <string>
#include <zmq.hpp>
#include <memory>

using context_ptr_t = std::shared_ptr<zmq::context_t>;
context_ptr_t global_context() {
    static context_ptr_t context = std::make_shared<zmq::context_t>(1);
    return context;
}

//////////////////////////////
class zmq_sink : public sink {
    std::string connection;
    context_ptr_t ctx;
    zmq::socket_t push;

  public:
    zmq_sink(std::string const &config, context_ptr_t c)
        : connection(config), ctx(c), push(*ctx, ZMQ_PUSH) {
            push.connect(connection);
        }

  public:
    bool send(std::string const & m) override { 
        zmq::message_t msg(m.length());
        memcpy((void *)msg.data(), m.data(), m.size());
        return push.send(msg);
    }

    std::string identity() const override { return "0mq:" + connection; }

    std::string config() const override { return connection; }
};

//////////////////////////////
class zmq_source : public source {
    std::string connection;
    context_ptr_t ctx;
    zmq::socket_t pull;    

  public:
    zmq_source(std::string const &config, context_ptr_t c)
        : connection(config), ctx(c), pull(*ctx,ZMQ_PULL) {
            pull.bind(connection);
        }

  public:
    std::string receive() override { 
        zmq::message_t request;
        pull.recv(&request);
        return std::move(std::string(static_cast<char*>(request.data()), request.size()));
    }

    std::string identity() const override { return "0mq:" + connection; }

    std::string config() const override { return connection; }
};

sink_ptr_t create_zmq_sink(std::string const &config) {
    return std::move(std::make_unique<zmq_sink>(config, global_context()));
}

source_ptr_t create_zmq_source(std::string const &config) {
    return std::move(std::make_unique<zmq_source>(config, global_context()));
}
