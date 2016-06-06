#pragma once

#include <middleware_contracts.h>

sink_ptr_t create_nanomsg_sink(std::string const& config);
source_ptr_t create_nanomsg_source(std::string const& config);
