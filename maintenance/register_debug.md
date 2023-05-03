# Vision FPGA Modules

There are 3 "modules" that comprise the vision system on the neuromorphic iCub
  - HPU Core: deal with data transfer from sensors, through the FPGA, to the CPU. The module uses the driver `/dev/iit-hpu0` and can only be accessed through this driver;
  - Vision Controller: deals with configuring the sensors (on/off, biases, ROI). Can be accessed directly through `/dev/i2c-X` where `X` is usually 1. A driver is being developed with a simpler API at `/dev/VSCtrlCore-L` and `/dev/VSCtrlCore-R`;
  - CCAM3 Controller: deals with other configuration of the FGPA. Can be accessed directly through `/dev/i2c-X` where `X` is usually 1. A driver is being developed with a simpler API at `/dev/CCAM3_IIT_GEN3-L` and `/dev/CCAM3_IIT_GEN3-R`.

you can check which drivers are inserted by using `lsmod` and looking for:

```
iit_vsctrl             16384  0
iit_ccam3_gen3         16384  0
iit_hpucore_dma        40960  0
```

If the module is insterted, you don't need to insert it again as described below.

### HPU

Insert the module:

`sudo insmod /home/drv/iit-hpucore-dma.ko rx_ps=8192 rx_pn=1024 tx_ps=8192 tx_pn=1024 test_dma=0 rx_to=3000 tx_to=3000`

To read register values of the HPU core use: 

`sudo cat /sys/kernel/debug/hpu/hpu.0x0000000080080000/regdump`

### Vision Controller

Insert the driver in development:

`sudo insmod /home/icub/iit-vsctrl.ko`

Read the registers:

`sudo cat /sys/kernel/debug/regmap/0-0010/registers`

`sudo cat /sys/kernel/debug/regmap/0-0011/registers`

### CCAM3 Controller

Insert:

`sudo insmod iit-ccam3-gen3.ko`

Read registers:

`sudo cat /sys/kernel/debug/regmap/0-0020/registers`

`sudo cat /sys/kernel/debug/regmap/0-0021/registers`

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


