# XY PWM Rotator

This project is the control firmware for a XY rotator using model servos and PWM signalling.<br>
It uses a subset of the GS-232B protocol.

# Configuring

The settings are located in [include/config.h](include/config.h) and have comments.

# Installing PlatformIO

I recommend using VSCode with PlatformIO, [instructions](https://docs.platformio.org/en/latest/integration/ide/vscode.html#installation).<br>
It can also be installed as [core](https://docs.platformio.org/en/latest/core/installation/index.html).<br>
Or with python venv:
```bash
python3 -m venv platformio
source platformio/bin/activate
pip install -U platformio
```

# Building

In VSCode under the PlatformIO Home, open this project directory.<br>
In the lower left ribbon, you have a small checkmark that starts the build.<br>
The icon with the arrow pointing to the right starts the uploader, it will try to figure out the serial port and upload with avrdude by default.

When using venv, you should start by sourcing the activate script in a terminal. It can be exited with `deactivate`.<br>
With venv/core:
```
pio run
pio run --target upload
```

# More boards

In [platformio.ini](platformio.ini) you can add more boards to build.
