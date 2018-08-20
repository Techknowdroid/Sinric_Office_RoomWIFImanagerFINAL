# Sinric_Office_RoomWIFImanagerFINAL
Using WIFI Manager to create an AP instead of hardcoded SSID and Password.


Techknowdroid VERSION 1.00 -  5th August,2018 
 Help taken from RandomNerd Tutorials  :  https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
 When your ESP8266 boots, it is set up in Station mode, and tries to connect to a previously saved Access Point (a known SSID and password combination);
 If this process fails, it sets the ESP into Access Point mode;
 Using any Wi-Fi enabled device with a browser, connect to the newly created Access Point (default name ESPConnectAP);
 After establishing a connection with the ESPConnectAP, you can go to the default IP address 192.168.4.1 to open a web page that allows you to configure your SSID and password;
 Once a new SSID and password is set, the ESP reboots and tries to connect;
 If it establishes a connection, the process is completed successfully. Otherwise, it will remain set up as an Access Point.
