#include "serial.h"

namespace esphome {
namespace intex_common {

void Serial::subscribe_receive(std::function<void(const uint8_t*, size_t)> callback) {
  this->receive_callback_ = callback;
}

void Serial::on_receive(const uint8_t* data, size_t length) {
  if (this->receive_callback_) {
    this->receive_callback_(data, length);
  }
}

}  // namespace intex_common
}  // namespace esphome
