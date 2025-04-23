#pragma once

#include "esphome/components/intex_common/lock_detector.h"
#include "esphome/components/intex_common/common_hmi.h"
#include "esphome/components/intex_common/timer_immobilizer.h"
#include "esphome/core/component.h"
#include "esphome/core/optional.h"
#include "esphome/components/uart/uart.h"
#include <array>
#include <cstdint>
#include <deque>

namespace esphome {
namespace switch_ {
class Switch;
}

namespace intex_sf90220rc1 {

class IntexSF90220RC1 : public Component, public uart::UARTDevice, public intex_common::CommonHmi {
  public:

    void setup() override;
    void loop() override;
    void dump_config() override;

    void set_power_switch(switch_::Switch *power_switch) { this->power_switch_ = power_switch; }

    optional<bool> is_power_on() const override;
    void press_power() override;

    optional<bool> is_locked() const override;
    void press_toggle_lock() override;

    TimerSetting timer_setting() const override;
    void press_increment_timer_setting() override;

  protected:
    void process_rx();
    void process_msg();
    bool read_display_msg(uint8_t& display_byte);

    void update_power_state(bool state, const char* source);
    void update_timer_state(uint8_t display_byte);

    intex_common::LockDetector lock_detector_;
    void update_lock_state(uint8_t display_byte, bool power_on);

    intex_common::TimerImmobilizer timer_immobilizer_{*this};

    bool try_tx(std::array<uint8_t, 4> message, const char *log_description = nullptr);
    static constexpr uint32_t kTxIntervalMillis = 250;
    uint32_t last_tx_{0};

    uint32_t last_auto_toggle{0};

    // discard at boot until frame timeout (might have woken up in the middle of a frame)
    bool receiving_{false};
    uint32_t last_rx_byte_time_{0};
    uint32_t last_rx_msg_time_{0};
    std::deque<uint8_t> rx_buf_;

    optional<bool> last_power_state_;
    optional<TimerSetting> timer_setting_;

    switch_::Switch *power_switch_{nullptr};
};

} //namespace intex_sf90220rc1
} //namespace esphome
