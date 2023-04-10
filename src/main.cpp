#include <iostream>

#include <co/http.h>
#include <co/time.h>

#include "httpServerConf.hpp"

auto main() -> int {
    http::Server().on_req(gd__::httpServerConf::httpOnReq).start("0.0.0.0", 9193);

    while (true) {
        sleep::sec(100);
    }

    return 0;
}