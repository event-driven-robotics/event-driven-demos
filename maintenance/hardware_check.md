### Ethernet connections
  - dhcp server -> switch
  - dhcp server -> external
  - icub-head -> switch
  - ultra-scale -> switch
  - alienwares (267/268) -> switch
  - your laptop will need to be connected to the switch via ethernet to access the robot/yarpserver

### DHCP Server (Wyse 5070)
  - It's really hard to tell if this is on. It gives the IP addresses to the whole system, so if you can't get an IP on the robot network it's probably that this one is off.

### Switch (Cisco)
  - Make sure it's on, there should be lights. If you can't get an IP address it's probably the DHCP server, but could be this is off.

### iiticublap267
  - this is the main YARP server computer. 
  - launch yarpmanager, etc. here.
 
### iiticublap268
  - this is additional compute power, and also the laptop connected to the screens to visualise the demos

### power supply (under the desk)
  - should be plugged in to desk power outlets.
  - turn on with button
  - 40 V / 12A

### icub-robot
  - the buttons on the backpack should light-up red.
  - turn on the CPU button
  - wait 10 seconds turn on the motors button.


