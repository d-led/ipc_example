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
        return !!push.send(m.c_str(), m.size() + 1, 0);
    }

    std::string identity() const override { return "nn:" + connection; }

    std::string config() const override { return connection; }
};

//////////////////////////////
class nanomsg_source : public source {
    std::string connection;
    nn::socket pull;
    char* buf = nullptr;

  public:
    nanomsg_source(std::string const &config)
        : connection(config), pull(AF_SP, NN_PULL) {
        pull.bind(config.c_str());
    }

  public:
    std::string receive() override {
      auto bytes = pull.recv(&buf, NN_MSG, 0);
        if ( bytes < 0) {
          return "";
        } else {
          std::string res(buf, buf + bytes);
          nn_freemsg(buf);
          buf = nullptr;
          return std::move(res);
        }
    }

    std::string identity() const override { return "nn:" + connection; }

    std::string config() const override { return connection; }
};

sink_ptr_t create_nanomsg_sink(std::string const &config) {
    return std::make_unique<nanomsg_sink>(config);
}

source_ptr_t create_nanomsg_source(std::string const &config) {
    return std::make_unique<nanomsg_source>(config);
}
