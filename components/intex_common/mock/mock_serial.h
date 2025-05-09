#pragma once
#include <gmock/gmock.h>

#include "../serial.h"

namespace esphome {
namespace intex_common {

class MockSerial : public Serial {
  public:
    MOCK_METHOD(void, send, (const uint8_t* data, size_t length), (override));
    MOCK_METHOD(void, subscribe_receive, (std::function<void(const uint8_t*, size_t)> callback),
                ());
};

}  // namespace intex_common
}  // namespace esphome
