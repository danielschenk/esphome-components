import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, switch
from esphome.const import CONF_ID

CODEOWNERS = ["@danielschenk"]
DEPENDENCIES = ['uart']
AUTO_LOAD = ['switch', 'intex_common']

CONF_PUMP_ID = 'pump_id'

intex_sf90220rc1_ns = cg.esphome_ns.namespace('intex_sf90220rc1')
IntexSF90220RC1 = intex_sf90220rc1_ns.class_('IntexSF90220RC1', cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(IntexSF90220RC1),
}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)

PUMP_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_PUMP_ID): cv.use_id(IntexSF90220RC1),
    }
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield uart.register_uart_device(var, config)
