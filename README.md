## xmas lights

### What?

A project to build and control a set of Christmas tree lights.
Each light an individually addressable RGB LED. The lights are 
on the local wifi. So any wifi connected device can send a 
pattern of colours to the lights. 

If The lights are scattered on a Christmas tree: then we need 
to determine the spatial co-ordinates of the lights in order 
to make spatially sensible patterns.

### Why?
Because it's fun. I started this project for the 2019 Christmas. 
I ended up missing that Christmas due to other work. I thought 
about it for 2020 but never got re-started. This is 2021 and 
it's looking good on timing.

### How?

WS2811 light strings. Driven by a wifi connected 
micro-controller. A set of scripts to capture and process 
position data. Scripts to drive patters of the lights. These 
scripts will utilise a laptop and web cam.

* Build the hardware.
  *   [Circuit descriptin](./arduino/wiring/README.md)
* Program the micro-controller
* Program a light controller
  * Set colour pattern
  * Derive the light positions
  * Set a spatial pattern

### Project structure

* `./arduino/wiring`
  * details the hardware
* `./arduino/wifi_neo_pixel`
  * arduino code
* `./python/spatial`
  * python project to determine the light positions.
* `./python/patterns`
  * python project to make a light show.