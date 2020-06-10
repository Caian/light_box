# light_box
A light box using a ws2812 LED strip for msp430g2553

## Pinout

```
MSP P1.2 ------   470 Ohm resistor   ------ ws2812b LED strip data in
MSP P1.3 ------ Normally Open Switch ------ GND
MSP P1.4 ------ Normally Open Switch ------ GND
MSP P1.5 ------ Normally Open Switch ------ GND
3V3 VCC  ------ ws2812b LED strip V+
GND      ------ ws2812b LED strip GND
```
