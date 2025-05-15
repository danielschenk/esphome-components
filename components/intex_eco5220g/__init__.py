import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@danielschenk"]
AUTO_LOAD = ['switch', 'intex_common']

CONF_CHLORINATOR_ID = 'chlorinator_id'
CONF_CLOCK_ID = 'clock_id'
CONF_SERIAL_ID = 'serial_id'

intex_eco5220g_ns = cg.esphome_ns.namespace('intex_eco5220g')
intex_common_ns = cg.esphome_ns.namespace('intex_common')
IntexECO5220G = intex_eco5220g_ns.class_('IntexECO5220G', cg.Component)
EspHomeMonotonicClock = intex_common_ns.class_('EspHomeMonotonicClock')
RmtSerial = intex_eco5220g_ns.class_('RmtSerial', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(IntexECO5220G),
    cv.GenerateID(CONF_CLOCK_ID): cv.declare_id(EspHomeMonotonicClock),
    cv.GenerateID(CONF_SERIAL_ID): cv.declare_id(RmtSerial),
}).extend(cv.COMPONENT_SCHEMA)

CHLORINATOR_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_CHLORINATOR_ID): cv.use_id(IntexECO5220G),
    }
)


def to_code(config):
    clock = cg.new_Pvariable(config[CONF_CLOCK_ID])
    serial = cg.new_Pvariable(config[CONF_SERIAL_ID])
    chlorinator = cg.new_Pvariable(config[CONF_ID], cg.RawExpression(f"*{clock}"),
                                   cg.RawExpression(f"*{serial}"))

    yield cg.register_component(serial, config)
    yield cg.register_component(chlorinator, config)
