#include "lakin_switch.h"
#include <cstdint>
#include "esphome/core/log.h"

#define REG_GPIO_CFG_BASE_ADDR (0x0802800)
#define GCFG_OUTPUT_POS 1
#define GCFG_OUTPUT_BIT (1 << 1)
#define REG_READ(addr)          (*((volatile uint32_t *)(addr)))
#define REG_WRITE(addr, _data)  (*((volatile uint32_t *)(addr)) = (_data))

namespace esphome {
namespace lakin {

static const char *const TAG = "lakin.switch";

static const int PIN_NUM = 22;

void LakinSwitch::dump_config() { LOG_SWITCH("", "Lakin", this); }
void LakinSwitch::setup() {
  ESP_LOGI(TAG, "Setting up Lakin '%s'...", this->name_.c_str());

  pinMode(PIN_NUM, OUTPUT);
}
void LakinSwitch::write_state(bool state) {
  ESP_LOGI(TAG, "Requested %s", state ? "On" : "Off");

  volatile uint32_t *gpio_cfg_addr = (volatile uint32_t *)(REG_GPIO_CFG_BASE_ADDR + PIN_NUM * 4);
  ESP_LOGI(TAG, "Address %04x", gpio_cfg_addr);

  uint32_t reg_val = REG_READ(gpio_cfg_addr);

  ESP_LOGI(TAG, "Val Read %04x", reg_val);
  // reg_val &= ~GCFG_OUTPUT_BIT;
  // ESP_LOGI(TAG, "Val Tweak %04x", reg_val);
  reg_val |= (state ? 1 : 0 & 0x01) << GCFG_OUTPUT_POS;
  ESP_LOGI(TAG, "Val Write %04x", reg_val);
  REG_WRITE(gpio_cfg_addr, reg_val);

  this->publish_state(state);
}

}  // namespace lakin
}  // namespace esphome
