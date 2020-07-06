**Install software environment for ACNode development**

**Ubuntu Desktop 18.04.3**

The instruction below is meant for a Ubuntu desktop 18.04.3 LTS based PC.

To install the different components, first open a terminal window in Ubuntu.

The following elements are part of the development environment:

- MQTT client (+ optional MQQT server/broker);
- Git server and git client;
- Arduino software

MQTT client and server

See for an overview of a number of clients: [https://www.hivemq.com/blog/seven-best-mqtt-client-tools/](https://www.hivemq.com/blog/seven-best-mqtt-client-tools/)

**MQTT server/broker:**

E.g. mosquitto:

Information: [https://mosquitto.org/](https://mosquitto.org/)

Download: [https://mosquitto.org/download/](https://mosquitto.org/download/)

**apt-add-repository ppa:mosquitto-dev/mosquitto-ppa**

**apt-get update**

**apt-get install mosquito -y**

or if there is already an older version of mosquitto installed:

**apt-get upgrade**

This broker runs in the background

**Install MQTT Clients:**

1. 1)Mosquitto

**apt-get install mosquitto-clients -y**

Open a terminal window to use this client. Available commands are:

**mosquitto\_sub**

**mosquitto\_pub**

1. 2)mqqt-cli

For more information see:

[https://hivemq.github.io/mqtt-cli/](https://hivemq.github.io/mqtt-cli/)

[https://github.com/hivemq/mqtt-cli](https://github.com/hivemq/mqtt-cli)

**wget** [**https://github.com/hivemq/mqtt-cli/releases/download/v1.0.1/mqtt-cli\_1.0.1\_all.deb**](https://github.com/hivemq/mqtt-cli/releases/download/v1.0.1/mqtt-cli_1.0.1_all.deb)

**apt install ./mqtt-cli\_1.0.1\_all.deb -y**

To use this client open a terminal window first. Use the following command to get an overview of the available commands:

**mqtt**

1. 3)MQTT.fx

Information: [**https://mqttfx.jensd.de/**](https://mqttfx.jensd.de/)

**wget** [http://www.jensd.de/apps/mqttfx/1.7.1/mqttfx-1.7.1-64bit.deb](http://www.jensd.de/apps/mqttfx/1.7.1/mqttfx-1.7.1-64bit.deb)

**apt install ./mqttfx-1.7.1-64bit.deb -y**

Check the installed applications in Ubuntu Desktop and click the icon **MQTTfx**.

**Installation of GIT:**

Information: [**https://git-scm.com/**](https://git-scm.com/)

**add-apt-repository ppa:git-core/ppa**

**apt update**

**apt install git -y**

Check git version:

**git --version**

**Git Client,** Git-cola:

Informatie: [**https://git-cola.github.io**](https://git-cola.github.io)

**apt-get install git-cola -y**

**Arduino:**

To use the Arduino software in combination with the ESP32 module in Ubuntu 18.04.3 LTS python and python-serial must be installed. To do this, open a terminal window and give the following commands:

**apt install python**

**apt install python-serial**

Information: [**https://www.arduino.cc/**](https://www.arduino.cc/)

Download: [**https://www.arduino.cc/download\_handler.php**](https://www.arduino.cc/download_handler.php)

Download the \*.tar.gz file to a folder of your own choice. Unpack this file. Run in a terminal window the install.sh file (to be found in the root directory of the unpacked files):

**./install.sh**

--------------------------------------------------------------------------------------------------------------------------------------

**Windows 10**

The instruction below is meant for a Windows 10 PC.

The following elements are part of the development environment:

- MQTT client (+ optional MQQT server/broker);
- Git server and git client;
- Arduino software

MQTT client and server

See for an overview of a number of clients: [https://www.hivemq.com/blog/seven-best-mqtt-client-tools/](https://www.hivemq.com/blog/seven-best-mqtt-client-tools/)

**MQTT server/broker:**

E.g. mosquitto:

Information: [https://mosquitto.org/](https://mosquitto.org/)

Download: [https://mosquitto.org/download/](https://mosquitto.org/download/)

This server/broker will be installed as a service on the Windows 10 PC.

Installation of Mosquitto server:

Download Mosquitto from [**https://mosquitto.org/download**](https://mosquitto.org/download)

Double click on the downloaded executable to install the Mosquitto service.

**Install MQTT Clients:**

1. 4)MQTT.fx

Information: [**https://mqttfx.jensd.de/**](https://mqttfx.jensd.de/)

Download ( **64 bit** Windows): [**http://www.jensd.de/apps/mqttfx/1.7.1/mqttfx-1.7.1-windows-x64.exe**](http://www.jensd.de/apps/mqttfx/1.7.1/mqttfx-1.7.1-windows-x64.exe)

Download ( **32 bit** Windows): [**http://www.jensd.de/apps/mqttfx/1.7.1/mqttfx-1.7.1-windows.exe**](http://www.jensd.de/apps/mqttfx/1.7.1/mqttfx-1.7.1-windows.exe)

Double click on the downloaded executable to install this client.

Press Start and look in the list for MQTT.fx to start this program.

**Installation of GIT:**

Information: [**https://git-scm.com/**](https://git-scm.com/)

Download: [**https://git-scm.com/download/win**](https://git-scm.com/download/win)

**Git Client,** Git-cola:

Informatie: [**https://git-cola.github.io**](https://git-cola.github.io)

Download: [**https://github.com/git-cola/git-cola/releases/download/v3.5/git-cola-3.5.windows.zip**](https://github.com/git-cola/git-cola/releases/download/v3.5/git-cola-3.5.windows.zip)

Unpack the downloaded ZIP file and double click dubbelklik the \*.exe. Accept all windows message and install the software.

**Arduino:**

Information: [**https://www.arduino.cc/**](https://www.arduino.cc/)

Download: [**https://www.arduino.cc/download\_handler.php**](https://www.arduino.cc/download_handler.php)

--------------------------------------------------------------------------------------------------------------------------------------

**Prepare Arduino for Makerspace Node software:**

After de Arduino software is installed, Arduino must be configured before it can be used to develop software for the nodes of the Makerspace.

**Olimex ESP32-PoE board:**

Install in Arduino the software for the Olimex ESP32-PoE board:

See e.g. the instructions on: [**https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/**](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

In short after starting the Arduino IDE software:

1. In the menu of the Arduino software click **File | Preferences**
2. In the Preference window shown add the following next to the text: Additional Boards Manager URLs:

**https://dl.espressif.com/dl/package\_esp32\_index.json,** [**http://arduino.esp8266.com/stable/package\_esp8266com\_index.json**](http://arduino.esp8266.com/stable/package_esp8266com_index.json)

1. Option: Also enable Display line numbers
2. Press the **OK** button
3. In the menu of the Arduino software select **Tools | Board: …** and click on **Boards Manager** in the menu popping up. Scroll to the bottom in the list shown or add esp32 to the search input box, until you see esp32. Click the Install button for the esp32 and close the window as soon as the software is installed
4. Select **Tools | Board: …** again but now scroll down in the list shown and select **OLIMEX ESP32‑PoE**

**Install libraries needed**

Use the Library Manager (Menu: **Tools | Manage Libraries…** ) of the Arduino ontwikkel to install the following libraries:

- **Adafruit GFX Library by Adafruit (versie 1.5.7)**
- **Adafruit SSD1306 by Adafruit (versie 1.3.0)**
- **ArduinoJson by Benoit Blanchon (versie 6.12.0)**
- **PubSubClient by Nick O&#39;Leary (versie 2.7.0)**

To speed up your search, add the name of the library, in the input box next to: **Filter your search…**

Press the **Install** button in the window showing  the library.

**Tip:** To edit certain source files in Windows 10 it might be handy to use a plain text editor tool e.g. Notepad++. Ubuntu already has a text editor available.

Information: [https://notepad-plus-plus.org/](https://notepad-plus-plus.org/)

Download: [https://notepad-plus-plus.org/downloads/](https://notepad-plus-plus.org/downloads/)

Notepad++ or another plain text editor is needed e.g. to edit PubSubClient.h after the library PubSubClient is installed.

In Windows 10 open the file D **ocumenten\Arduino\libraries\PubSubClient\src\PubSubClient.h** in e.g. Notepad++

In Ubuntu use **Files** and select in **Home** the following director:

**Arduino/libraries/PubSubClient/src**

Double click PubSubClient.h in this directory to open this file in the text editor.

In both cases change the value next to   **MQTT\_MAX\_PACKET\_SIZE** from **128** to **1290** , as shown below:

**#define MQTT\_MAX\_PACKET\_SIZE 1290**

Save this file and close Notepad++ in Window 10 or Text Editor in Ubuntu

The following libraries cannot be installed with the Arduino Library manager. To install these libraries:

Open each of the following urls&#39;s in a webbrowser, click in the window shown on the **Clone or download** button and then on the **Download ZIP** button, save the ZIP file in a directory of your own choice.

In Windows 10 copy the content of all these ZIP files to the directory ** Documenten\Arduino\libraries**.

In Ubuntu do the same to the directory

**Arduino/libraries in your Home directory**

[**https://github.com/dirkx/OptocouplerDebouncer**](https://github.com/dirkx/OptocouplerDebouncer)

[**https://github.com/dirkx/CurrentTransformer**](https://github.com/dirkx/CurrentTransformer)

[**https://github.com/dirkx/ButtonDebounce**](https://github.com/dirkx/ButtonDebounce)

[**https://github.com/dirkx/base64\_arduino.git**](https://github.com/dirkx/base64_arduino.git)

[**https://github.com/dirkx/rfid.git**](https://github.com/dirkx/rfid.git)

[**https://github.com/prphntm63/WIFIMANAGER-ESP32**](https://github.com/prphntm63/WIFIMANAGER-ESP32)

Do the same fort the following link, but unpack the ZIP file first e.g. in the directory where the ZIP file was downloaded to.

[**https://github.com/dirkx/AccesSystem**](https://github.com/dirkx/AccesSystem) ** **

Windows 10: Open in Windows explorer the directory in the unpacked ZIP file:   **……\AccesSystem-master\lib-arduino\**

Copy the sub directory **ACNode** to the Windows directory **Documenten\Arduino\libraries**.

For Ubuntu do the same but copy ACNode to the **Arduino/libraries** directory in your Home directory.

Do the same for the link [**https://github.com/rweather/arduinolibs.git**](https://github.com/rweather/arduinolibs.git), also unpack this ZIP file and go to the directory **…..\arduinolibs-master\libraries\**. Copy the subdirectories **Crypto** and **CryptoLegacy** to the Windows directory **Documenten\Arduino\libraries**.

For Ubuntu do the same but copy **Crypto** and **CryptoLegacy** to the **Arduino/libraries** directory in your Home directory.

Open in the Arduino  development software de **SampleNode** sketch:

Click left in the top of the Arduino window on the menu item **File** , then: **Examples | ACNode | SampleNode**

 A new Arduino window is opened. with SampleNode sketch. Use File | Save As… to save this sketch as **SampleNode**.

The Arduino software is now ready to compile the sketch and download it in the ESP32.

**Tip:** default the Serial monitor tool (Menu: **Tools | Serial Monitor** ) is configured with a baudrate of 9600, while the SampleNode sketch expects a baudrate of 115200. To do this you first have to connect the ESP32 to the PC and set the correct serial port (Menu: **Tools | Port** ).
