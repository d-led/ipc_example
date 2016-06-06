#pragma once

#include <memory>
#include <string>

struct identifyable {
    virtual std::string identity() const = 0;
    ~identifyable() {}
};

struct source : identifyable {
    virtual std::string receive() = 0;
    virtual ~source() {}
};

struct sink : identifyable {
    virtual bool receive(std::string const &) = 0;
    virtual ~sink() {}
};

using sink_ptr_t = std::unique_ptr<sink>;
using source_ptr_t = std::unique_ptr<source>;
