# iCub Software Update

## Software Version Check

We use the [latest stable version](https://icub-tech-iit.github.io/documentation/sw_versioning_table/#software-versioning-table) of robotology-superbuild.

### iiticublap267 & 268

* `cd /usr/local/src/robot/robotology-superbuild/build` 
* `git status` 

git status should give the same as [latest stable version]

### icub-head

First of all, turn on iCub CPU and motors. Before updating the firware, let's check the robotology-superbuild is on its latest version.

* `ssh icub-head`
* `cd /usr/local/src/robot/robotology-superbuild/build` 
* `git status`  
git status should give the same as [latest stable version]

In addition to robotology-superbuild we need to check-out icub-firmware-build with the compatible version listed in the [software-versioning-table](https://icub-tech-iit.github.io/documentation/sw_versioning_table/#software-versioning-table)

* `cd /usr/local/src/robot/icub-firware-build/build` 
* `git status`  
git status should give the same as the version for icub-firmware-build of [latest stable version]

## Updating Software

If the version of robotology-superbuild or icub-firmware-build does not corrispond to the [latest stable version], you should update them

### robotology-superbuild (on iiticublap267, 268 and icub-head)
* `cd /usr/local/src/robot/robotology-superbuild/build` 
* `git pull`
* `make update-all` 
* `make`

### icub-firmware-build (only on icub-head)
* check you are inside icub-head `ssh -X icub@icub-head`. The parameter `-X` is needed to open GUIs
* `cd /usr/local/src/robot/icub-firmware-build/build` 
* `git pull`
* `make update-all` 
* `make`
* type `FirmwareUpdater -a` to open the software with admin privilege
* click on ETH row (1) and on discover button (2)
 ![discover](https://user-images.githubusercontent.com/45895918/166433907-1d8d7872-8252-49e2-b976-2ab94cf47122.png)
* we recommend take a screenshot of the GUI to save the boards status before updating it
* select one EMS from the list (1) and then click on select all (2)
* click Force ETH Maintenance button
![Force_mantainance](https://user-images.githubusercontent.com/45895918/166434345-f322c9a5-7278-4521-ab51-1d3c0362bf26.png) and check boards are on maintenance and the processes are set to eUpdater with versions different from the eApplication 
* select again all ems4 and click on Upload Application button 
![Upload_application](https://user-images.githubusercontent.com/45895918/166434631-da88079c-b5cd-4dd8-8e1f-74d61749bdb1.png)
* select the corresponding ems4 application file inside `/usr/local/src/robotology-superbuild/icub_firmware_build/ETH/EMS/bin/application`
* repeat the previous three commands for other boards (e.g. mc4plus) and select their corresponding application files
* turn off and then back on the motors of icub (button on the side of icub)
* run `yarprobotinterface` to verify the robot is starting and calibrating correctly

### event-driven (only on icub-zynq)
* update YCM, YARP to identical versions as other systems
* update event-driven to master
