
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

#How to use it?
### Step 1: Extract segnix.zip
You should extract segnix.zip and focus on the README.md file.

### Step 2: Install segnix
You can use "make" ,Then use "make install". 
 
### Step 3: Use segnix compile server.c or use directly later server
You can use "segnix server.c" 

### Step 4: Use segnix compile AlarmSystem or directly later AlarmSystem
You can use "segnix AlarmSystem.ino" 

### Step 5: Open a window Execute "server"
You can use "./server".

### Step 6: Open the other window Execute "AlarmSystem"
You can use "./AlarmSystem".

### Step 7: Alarm message
 There will be a phone call later. You can pick up the phone and hear the alarm.
You can press 1 or 2 with another alarm to ring off for a while.

# Folder description
-	source：
	
	24.mp3 25.mp3 26.mp3 : Recording file.

	server.c : the server source code
	
	server : server Executable file

	AlarmSystem.ino :main source code

	AlarmSystem : AlarmSystem Executable file

-	segnix.zip: segnix Installation package

-	README.md 	
