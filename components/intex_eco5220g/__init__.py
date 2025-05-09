import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@danielschenk"]
AUTO_LOAD = ['switch', 'intex_common']

CONF_CHLORINATOR_ID = 'chlorinator_id'

intex_eco5220g_ns = cg.esphome_ns.namespace('intex_eco5220g')
IntexECO5220G = intex_eco5220g_ns.class_('IntexECO5220G', cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(IntexECO5220G),
}).extend(cv.COMPONENT_SCHEMA)

CHLORINATOR_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_CHLORINATOR_ID): cv.use_id(IntexECO5220G),
    }
)


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
