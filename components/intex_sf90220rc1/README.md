# Intex SF90220RC1 pool filter pump

## ⚠️ **This is a work in progress** ⚠️

```yaml
# example configuration:

intex_sf90220rc1:
  id: pool_pump

switch:
  - platform: intex_sf90220rc1
    pump_id: pool_pump
    power_switch:
      id: pool_pump_power_switch
      name: pool_pump_power_switch

uart:
  tx_pin: GPIO32
  rx_pin: GPIO33
  baud_rate: 2400
```
