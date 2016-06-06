#include <nanomsg_factory.h>

//////////////////////////////
class nanomsg_sink : public sink {
    std::string connection;

  public:
    nanomsg_sink(std::string const &config) : connection(config) {}

  public:
    bool send(std::string const &) override { return false; }

    std::string identity() const override {
        return "nn:" + connection;
    }

    std::string config() const override { return connection; }
};

//////////////////////////////
class nanomsg_source : public source {
    std::string connection;

  public:
    nanomsg_source(std::string const &config) : connection(config) {}

  public:
    std::string receive() override { return ""; }

    std::string identity() const override {
        return "nn:" + connection;
    }

    std::string config() const override { return connection; }
};

sink_ptr_t create_nanomsg_sink(std::string const &config) {
    return std::move(std::make_unique<nanomsg_sink>(config));
}

source_ptr_t create_nanomsg_source(std::string const &config) {
    return std::move(std::make_unique<nanomsg_source>(config));
}
