# LittleMoon
This is the framework of a clever Bialetti style clock like this. The main feature is a very simple 8x8 led matrix able to show some simple and clean informations: 
![Image of Bialetti Clock](https://trello-attachments.s3.amazonaws.com/5e575a782c30e258eadd66c1/5e89ea634993527e5eee9e5d/b163e654d9fe9de7374228751c0b2f07/IMG_20200415_111036.jpg)
## 1.0.0
First release include the moon pahses management. Phases are shown into the 8x8 matrix through 12 steps following the real moon position:

![Image of Moon Phases](https://trello-attachments.s3.amazonaws.com/5e575aec574d02803b182c34/333x89/3473a8468bbb4b27107f9f5dba24c88b/image.png)

On first boot the display will show a "conf" message:  

![conf gif](https://trello-attachments.s3.amazonaws.com/5e89cb14db1c416298a5b7c2/320x320/6ebfd07afe094c10aed6bd4dd5d7a81e/giphy1390469578960355226.gif)

Using the famous [wifiManger](https://github.com/tzapu/WiFiManager) library you'll be able to configure the wifi connection and after this the clock will be initialized and synch using configTime and ntp connection. 
The moon phase is calculated using the alghoritm developed into moon_phases_lib. 

