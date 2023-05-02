### Insert Debug Modules
The following modules are required to perform some of the debug operation described here:

`sudo insmod iit_ccam3_gen3.ko`

`sudo insmod iit_vsctrl.ko`

you can check they are already inserted with:

`sudo lsmod`

### Read HPU Registers
To read register values of the HPU core use: 

`sudo cat /sys/kernel/debug/hpu/hpu.0x0000000080080000/regdump`

for Eyes' register, you have to use:

0020 is the LEFT eye main register set

`sudo cat /sys/kernel/debug/regmap/0-0020/registers`

0021 is the RIGHT eye main register set

`sudo cat /sys/kernel/debug/regmap/0-0021/registers`

n order to view registers from Vision Controller, you can use:

`sudo cat /sys/kernel/debug/regmap/0-0010/registers`

`sudo cat /sys/kernel/debug/regmap/0-0011/registers`

0010 is the Vision Controller of LEFT eye
0011 is the Vision Controller of RIGHT eye

### Biases
To debug bias names and values you can use the `vsctrl` application as:

`sudo ./vsctrl -X getbtab` where `-X` is `-l` for left and `-r` for right.

To get an individual bias use, for example:
`sudo ./vsctrl -r getbias Bias_sendreq_pdy`

To set biases use, for example:
`sudo ./vsctrl -r setbias Bias_sendreq_pdy 141`

### Transceiver
In order to make clock of the Transceiver run:

`source ./start_clock.sh`


