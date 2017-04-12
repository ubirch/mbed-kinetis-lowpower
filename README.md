# Kinetis low power modes

This is a library to enable low power modes on Kinetis MCUs. Depending on the MCU there are quite a lot of different
power modes available.

- VLLS0 is used to maximally power down
- pin interrupt and RTC modes are currently supported to wake up

## Usage

Add this library to your mbed application: `mbed add https://github.com/ubirch/mbed-kinetis-lowpower`, use the 
library functions and run your code. Examples are provided in the [example](example) subdirectory.

The code has been tested on a K82F on our [ubirch](https://ubirch.com) board.

## Testing

Link the example into the project directory and compile:

- `ln -sf example/pin_wakeup.cpp main.cpp`
- `mbed target UBIRCH`
- `mbed toolchain GCC_ARM`
- `mbed compile`

## License

If not otherwise noted in the individual files, the code in this repository is

__Copyright &copy; 2017 [ubirch](http://ubirch.com) GmbH, Author: Matthias L. Jugel, Niranjan Rao__

```
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

