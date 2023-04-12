#include <iostream>

#include <co/http.h>

#include "httpServerConf.hpp"

auto main() -> int {
    http::Server().on_req(gd__::httpServerConf::httpOnReq).start("0.0.0.0", 9193);

    so::easy(".", "0.0.0.0", 9194);

    return 0;
}