import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import CONF_ID, ICON_POWER
from .. import CONF_PUMP_ID, PUMP_COMPONENT_SCHEMA, intex_eco5220g_ns

DEPENDENCIES = ['intex_eco5220g']

CONF_POWER_SWITCH = 'power_switch'

PowerSwitch = intex_eco5220g_ns.class_("PowerSwitch", switch.Switch, cg.Component)

SWITCH_SCHEMA = switch.switch_schema(
    PowerSwitch, icon=ICON_POWER
).extend(cv.COMPONENT_SCHEMA)

CONFIG_SCHEMA = PUMP_COMPONENT_SCHEMA.extend(
    {cv.Optional(CONF_POWER_SWITCH): SWITCH_SCHEMA}
)


def to_code(config):
    paren = yield cg.get_variable(config[CONF_PUMP_ID])

    if CONF_POWER_SWITCH in config:
        config = config[CONF_POWER_SWITCH]
        var = cg.new_Pvariable(config[CONF_ID])
        yield switch.register_switch(var, config)
        cg.add(var.set_parent(paren))
        cg.add(paren.set_power_switch(var))
