# MOUSE DRIVER  
***Which one to use?***  
If you're using an usb shield, you need to connect your mouse on the shield and the shiel on the PC, then upload [shield driver](VMouse/USBHostShield.ino).  
If you're using only an arduduino leonard/pro micro use the [VMouse driver](VMouse/VMouse.ino).  

## The difference  
The shield driver will read the mouse value and then recreate them. It will work like you're using only one mouse on the computer.  
Without the shield, it will only read the value and create the movement like a second mouse.
