#pragma once

#include <middleware_contracts.h>

sink_ptr_t create_sink(std::string const& config);
source_ptr_t create_source(std::string const& config);
