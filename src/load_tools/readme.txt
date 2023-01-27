You should start loadTools.sh to load the jar files from internet. 
You need java in your computer. (JRE8 currently).

You may have this tools directory not only in your workspace, 
* but also centralized on ~/vishia/tools in your home location
* or maybe in /usr/vishia/tools centralized for a Linux computer
* or maybe in C:\Programs\vishia\tools on a Windows computer. 

The you can make a link to the tools directory in your working tree with the command:

 mklink /J tools c:\Programs\vishia\tools  (windows) or
 ln -s /usr/vishia/tools tools 
 
The directory cmds_template contains files, which should be placed on the ~/cmds/* location
also for windows and linux. 
They are called from some scripts using "~/cmds/jztxtcmd.sh script"
or "/cmds/javavishia.sh path.to.mainfile ...args".
You should adapt some settings in this file for your conditions. 

