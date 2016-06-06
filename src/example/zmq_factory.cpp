#include <zmq_factory.h>
#include <string>

//////////////////////////////
class zmq_sink : public sink {
    std::string connection;

  public:
    zmq_sink(std::string const &config) : connection(config) {}

  public:
    bool send(std::string const &) override { return false; }

    std::string identity() const override {
        return "0mq:" + connection;
    }

    std::string config() const override { return connection; }
};

//////////////////////////////
class zmq_source : public source {
    std::string connection;

  public:
    zmq_source(std::string const &config) : connection(config) {}

  public:
    std::string receive() override { return ""; }

    std::string identity() const override {
        return "0mq:" + connection;
    }

    std::string config() const override { return connection; }
};

sink_ptr_t create_zmq_sink(std::string const &config) {
    return std::move(std::make_unique<zmq_sink>(config));
}

source_ptr_t create_zmq_source(std::string const &config) {
    return std::move(std::make_unique<zmq_source>(config));
}
