# VALORANT  
Undetected external cheat using HSV color detection.  
This will not mess with the addresses and memories of the game, it's 100% memory independent.  
  
Customizable via menu.  
- Panic key is 'Del', press it to exit the cheat.  
  
![preview](prev.png)    
  
# WARNING  
This project won't be continued.  
I've not tested the cheat since 'first commit' release date.  

## COMPILATION   
Comment [line 22 before compiling!](Valorant/new/Manager.cpp#L22) otherwise it wont allow you to use, it is a simple HWID license checker that i'll use in the future.  
You need to download [GLFW pre-compiled binaries](https://www.glfw.org/download) and add the `/include` folder to the Include path.  
Also include `/vs-XXXX` (XXXX = Visual Studio Version, ex: vs-2022 for VStudio 2022) to the lib folder. 
  
# INFO    
- Change the saturation if it starts missing too much.  
The default saturation is 15 - 80 (Min - Max)     
  
Only the RCS Require arduino with usb/mouse signature   
	- Push the desired [arduino driver](VMouse/readme.md) to arduino before using RCS.  
	  
# Issues
Do not open for questions like  
	- Does it works on ...  
	- Can i use red outline ...  
	- Can you make one private for me  
  
Feel free to make pull/reqs or collaborate.   
