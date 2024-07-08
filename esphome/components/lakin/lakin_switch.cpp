#include "lakin_switch.h"
#include "esphome/core/log.h"

namespace esphome {
namespace lakin {

static const char *const TAG = "lakin.switch";

void LakinSwitch::dump_config() { LOG_SWITCH("", "Lakin", this); }
void LakinSwitch::setup() {
  ESP_LOGI(TAG, "Setting up Lakin '%s'...", this->name_.c_str());

  pinMode(22, INPUT);
}
void LakinSwitch::write_state(bool state) {
  LOG_SWITCH("", state ? "On" : "Off", this);

  digitalWrite(22, state);

  // this->publish_state(state);
}

}  // namespace lakin
}  // namespace esphome
