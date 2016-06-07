#include <zmq_factory.h>
#include <string>
#include <zmq.hpp>
#include <zmq_addon.hpp>
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
        : connection(config), ctx(c), push(*ctx, ZMQ_DEALER) {
            push.connect(connection);
        }

  public:
    bool send(std::string const & m) override {
        zmq::multipart_t msg(m.data(),m.length());
        return msg.send(push);
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
        : connection(config), ctx(c), pull(*ctx,ZMQ_ROUTER) {
            pull.bind(connection);
        }

  public:
    std::string receive() override {
        zmq::multipart_t request(pull);
        request.pop();
        return request.popstr();
    }

    std::string identity() const override { return "0mq:" + connection; }

    std::string config() const override { return connection; }
};

sink_ptr_t create_zmq_sink(std::string const &config) {
    return std::make_unique<zmq_sink>(config, global_context());
}

source_ptr_t create_zmq_source(std::string const &config) {
    return std::make_unique<zmq_source>(config, global_context());
}
