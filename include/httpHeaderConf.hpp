#pragma once

#include <string>

namespace gd__ {
    struct httpHeaderConf {
        static constexpr char const * kOperation {"operation"};
        static constexpr char const * kResult {"result"};
        static constexpr char const * kReason {"reason"};

        static constexpr char const * kIdentify {"identify"};

        static constexpr char const * kSuccess {"success"};
        static constexpr char const * kFailed {"failed"};

        static constexpr char const * kImg {"img"};
    };
}