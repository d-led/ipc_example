#include <nanomsg_factory.h>
#include <nn.hpp>
#include <nanomsg/pipeline.h>

//////////////////////////////
class nanomsg_sink : public sink {
    std::string connection;
    nn::socket push;

  public:
    nanomsg_sink(std::string const &config)
        : connection(config), push(AF_SP, NN_PUSH) {
        push.connect(config.c_str());
    }

  public:
    bool send(std::string const &m) override {
        return push.send(m.c_str(), m.size() + 1, 0);
    }

    std::string identity() const override { return "nn:" + connection; }

    std::string config() const override { return connection; }
};

//////////////////////////////
class nanomsg_source : public source {
    std::string connection;
    nn::socket pull;
    char buf[512];

  public:
    nanomsg_source(std::string const &config)
        : connection(config), pull(AF_SP, NN_PULL) {
        pull.bind(config.c_str());
    }

  public:
    std::string receive() override {
        if (pull.recv(buf, sizeof(buf), 0) >= 0) {
            return buf;
        } else {
            return "";
        }
    }

    std::string identity() const override { return "nn:" + connection; }

    std::string config() const override { return connection; }
};

sink_ptr_t create_nanomsg_sink(std::string const &config) {
    return std::move(std::make_unique<nanomsg_sink>(config));
}

source_ptr_t create_nanomsg_source(std::string const &config) {
    return std::move(std::make_unique<nanomsg_source>(config));
}
