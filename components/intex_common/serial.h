#pragma once

#include <array>
#include <cstdint>
#include <functional>

namespace esphome {
namespace intex_common {

// Interface for serial communication
class Serial {
  public:
    virtual ~Serial() = default;

    template <size_t N>
    void send(const std::array<uint8_t, N>& data) {
      this->send(data.data(), N);
    }

    virtual void send(const uint8_t* data, size_t length) = 0;

    void subscribe_receive(std::function<void(const uint8_t*, size_t)> callback);

  protected:
    // This function is called when data is received
    void on_receive(const uint8_t* data, size_t length);

  private:
    std::function<void(const uint8_t*, size_t)> receive_callback_;
};

}  // namespace intex_common
}  // namespace esphome
