import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import output, switch
from esphome.const import CONF_OUTPUT
from .. import output_ns

LakinSwitch = output_ns.class_("LakinSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = cv.all(
    cv.only_with_arduino,
    switch.switch_schema(LakinSwitch)
    # .extend(
    #     {
    #         cv.Required(CONF_PIN): pins.internal_gpio_output_pin_number,
    #     }
    # )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)

    # output_ = await cg.get_variable(config[CONF_OUTPUT])
    # cg.add(var.set_output(output_))
