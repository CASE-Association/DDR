# DDR Lighting & control
Remote control and lighting effects for the CASE Dance Dance Revolution vehicle. 

- `cortege_on_esp`: receiver for MIT App Inventor control.
- `neopixel_relay`: emulates Enter & Esc, pushes lighting data from serial to the neopixels.
- `outfox-lights`: reads lighting from OutFox memory, generates lighting effects sent to the above.

OutFox shipped separately!

# DDR-dator usage
Download the latest release from the sidebar. Inside it, there's two apps. Double-click and launch both.

- `outfox-lights`: Extracts lighting data from OutFox. Just start and leave be
- `stepmania.exe`: Reads the lighting data and sends it over serial to the lights. It must have its dependencies in the `stepmania\` folder with it!
