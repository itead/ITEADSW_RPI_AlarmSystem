
# AlarmSystem  Software

-	Author：huang xianming	
-	Time:2015-9-8 18:04:44

--------------------------------------------------------------------------------
# What Is It?
AlarmSystem is Intelligent voice alarm system based on SIM module and Raspberry
pie, Use segnix Compile . First ,You should extract the segnix focus on the 
README.md file inside the segnix.There are detailed steps to use segnix, I 
believe you will understand! In addition,Raspberry pie System is 2015-02-16-
raspbian-wheezy.



# How to use it?
### Step 1: Extract segnix.zip
You should extract segnix.zip and focus on the README.md file.

### Step 2: Install segnix
You can use "sudo make" ,Then use "sudo make install". 
 
### Step 3: Use segnix compile server.c or use directly later server
You can use "sudo segnix server server.c" 

### Step 4: Use segnix compile AlarmSystem or directly later AlarmSystem
You can use "sudo segnix AlarmSystem AlarmSystem.ino" 

### Step 5: Execute "server"
You can use "sudo ./server &".

### Step 6: Execute "AlarmSystem"
You can use "sudo ./AlarmSystem".

### Step 7: Alarm message
 There will be a phone call later. You can pick up the phone and hear the alarm.
You can press 1 or 2 with another alarm to ring off for a while.

# Warning!
Frist,you  must install mplayer:
	
	sudo apt-get install mplayer
Second,you must disable serial.

	sudo raspi-config
   	————>  8 Advanced Options  ————> A8 Serial ————>NO

# Folder description
-	source：
	
	24.mp3 25.mp3 26.mp3 : Recording file.

	server.c : the server source code
	
	server : server Executable file

	AlarmSystem.ino :main source code

	AlarmSystem : AlarmSystem Executable file

-	segnix.zip: segnix Installation package

-	README.md 	
