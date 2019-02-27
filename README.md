# CAN-Message-injector
This is an arduino based project showing how to interface CAN module

The project shows how the status of different devices are checked and according to the status a message is sent (CAN Message) on the CAN bus. The CAN is the abbreviation for Controller Area Network which is usually found in vehicles/electric vehicles. 

For more information about CAN, please visit https://en.m.wikipedia.org/wiki/CAN_bus

The project requires an Arduino (one used in this is Uno) and CAN module (one used in this project is MCP2515). 

The status signals of IMD, BSPD, AMS, SW (devices taken for example - IMD= Insulation Monitoring Device,BSPD= Break System Plausability Device, AMS= Accumulator Management System, SW= Shutdown sWitch) are read into Arduino microcontroller’s pins 2, 4, 6, 8 respectively. When detected an error the CAN module sends a particular unique CAN frame corresponding to the error source into the CAN bus. Different frames sent, corresponding to the different errors are given in the table (https://github.com/sudheendra-hegde/CAN-Message-injector/blob/master/IMG_20190227_173251.jpg). Also, a unique CAN frame is put into the CAN bus, representing that no more errors exist, after an error is corrected. By default if no error is detected, no CAN frame is transmitted by the CAN module. 
Here is the wiring diagram - https://github.com/sudheendra-hegde/CAN-Message-injector/blob/master/IMG_20190227_173310.jpg
