# Sinric_Office_RoomWIFImanagerFINAL
Using WIFI Manager to create an AP instead of hardcoded SSID and Password.


Techknowdroid VERSION 1.00 -  5th August,2018 
 Help taken from RandomNerd Tutorials  :  https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
 When your NodeMcu(esp8266) boots, it is set up in Station mode, and tries to connect to a previously saved Access Point (a known SSID and password combination);
 If this process fails, it sets the ESP into Access Point mode;
 Using any Wi-Fi enabled device with a browser, connect to the newly created Access Point (default name ESPConnectAP);
 After establishing a connection with the ESPConnectAP, you can go to the default IP address 192.168.4.1 to open a web page that allows you to configure your SSID and password;
 Once a new SSID and password is set, the NodeMcu(esp8266) reboots and tries to connect;
 If it establishes a connection, the process is completed successfully. Otherwise, it will remain set up as an Access Point.

A 20x4 LCD is connected to the NodeMcu(esp8266) to show the status of events.
The Pin SCL on the LCD Panel goel to D1(GPIO 5) on the NodeMcu
The Pin SDA on the LCD Panel goel to D2(GPIO 4) on the NodeMcu
