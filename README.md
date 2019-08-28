## VacuumCleanerRobotGarage
VacuumCleanerRobotGarage is a project to create garage for my xiaomi vacuum cleaner.
It have ability to periodically open it's gates to allow vacuum cleaner performing cleanup,
and it close automatically once cleaning is performed.

## Wirings

![Design](http:/https://raw.githubusercontent.com/loen/VacuumCleanerRobotGarage/master/designs/VacuumCleanerRobotGarage.jpg)

## How to setup bluetooth connectivity on Raspberry Pi

Login to your Raspberry Pi and run bluetoothctl program in terminal. 
```
$ sudo bluetoothctl
```

Than in that program execute following commands, where **XX:XX:XX:XX:XX:XX** is mac address of  VacuumCleanerRobotGarage device:

```
$ agent on
$ default agent
$ scan on
$ pair XX:XX:XX:XX:XX:XX
$ trust XX:XX:XX:XX:XX:XX
```

after that your Raspberry Pi and VacuumCleanerRobotGarage will be paired, that's not mean they are connected since **HC-05** 
bluetooth module emulates **UART** bluetooth connection will be established once one device will try to send something via serial
port emulated by paired bluetooth devices. In order to create such virtual port on Raspberry Pi you have to execute following
command, where **XX:XX:XX:XX:XX:XX** is mac address of  VacuumCleanerRobotGarage device:

```
$ sudo rfcomm bind 0 XX:XX:XX:XX:XX:XX 1
```

after this you are able to send text message to VacuumCleanerRobotGarage device using following command:

```
$ echo "TEST-MSG" > /dev/rfcomm0
```
