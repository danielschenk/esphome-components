#pragma once

namespace esphome {
namespace intex_common {

class Lockable {
  public:
    virtual void toggle_lock() = 0;
};

}
}
