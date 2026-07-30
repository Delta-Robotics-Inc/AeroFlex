# AeroFlex clean-slate safety firmware

This is a separate, deliberately inert Arduino Uno R4 Minima firmware for
isolating software from a rig fault. It does **not** replace or modify the
normal commissioning firmware in `../firmware/`.

## Safety behavior

- D6 (STEP) and D5 (DIR) remain `INPUT` (high impedance).
- All other documented rig signal pins also remain `INPUT`.
- It emits only USB serial status at 115200 baud.
- It accepts no serial commands and cannot command motor motion.

It cannot repair a short, damaged wire, failing driver, incorrect supply
connection, or mechanical binding. Do not reconnect 24 V motor power merely to
test this sketch. Investigate any heat, odor, or smoke with all power removed.

## Upload

1. Turn off/disconnect the rig's 24 V motor supply. Leave the 9 V barrel plug
   disconnected. Close the dashboard and Arduino IDE/Serial Monitor so COM3 is
   free.
2. Connect only the Arduino USB cable.
3. Run from PowerShell:

   ```powershell
   cd C:\Users\Charles\Desktop\Repos\AeroFlex\firmware-clean-slate
   & "$env:APPDATA\Python\Python314\Scripts\pio.exe" run --target upload
   ```

4. A serial monitor at 115200 baud will show `@SAFE ... motion=disabled` once
   per second. The live test-rig dashboard will show this in its raw console,
   but it will not enter `PROTOCOL V1` because clean-slate has no telemetry or
   motion interface.

To resume the normal test-rig firmware later, upload `../firmware/` again only
after the mechanical and electrical inspection is complete.
