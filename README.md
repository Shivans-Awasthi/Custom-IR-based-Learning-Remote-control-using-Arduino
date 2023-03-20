# ARDUINO BASED LEARNING UNIVERSAL REMOTE
This project explains how to use an Arduino to construct an intelligent learning custom IR remote control that can control any electronic device that comes with an IR remote control. It is based on the concept of how it is possible to receive, decode and send IR signals using an Arduino and the simple IRremote library. Index Terms- Arduino based learning universal remote, Arduino projects, Arduino applications , Beginner and advanced Arduino projects, DIY Universal remote control. 

# I. INTRODUCTION 
Infrared communication is among the simplest wireless communication methods, and it serves as a cost-effective way of transmitting a few bits of data wirelessly. It’s safe to assume anyone reading this has used many different remote controls at home or work, and most of those simple devices communicate with the receiver via infrared pulses.The aim of the project is to construct an Universal learning remote using an Arduino and an open source IRremote Arduino library. The project covers both Hardware and Software aspects of the construction. 

# II. STUDY OF SIMILAR PROJECTS OR TECHNOLOGY/LITERATURE REVIEW
Other similar projects used Arduino Nano and Arduino Micro as their micro-controller board and used an ATtiny85 micro-controller IC to store the replicated key data instead of Arduino itself. One of them used a SD card to store around 400 replicated key data of multiple devices and switch between them using two rotary encoders, they also used a boost converter(<5V to 5V) with rechargeable lithium battery. 

# III. BASIC CONCEPTS/TECHNOLOGY USED 
Infrared communication: Infrared communication is point to point communication between two devices with close proximity to one another. Infrared radiation is the region of the electromagnetic spectrum between microwaves and visible light. In infrared communication, an LED transmits the infrared signal as bursts of non-visible light. At the receiving end a photo-diode or photoreceptor detects and captures the light pulses, which are then processed to retrieve the information they contain.[1] Arduino: Arduino is an open-source hardware and software company, project, and user community that designs and manufactures single-board micro-controllers and micro-controller kits for building digital devices.[2] Basic knowledge of electronics and electric circuits: You may need a basic understanding of concepts of transistors, resistors and circuit creation and its working to fully understand the project.

# IV. PROPOSED MODEL/ARCHITECTURE/METHODOLOGY/MODEL TOOL 
The following schematic shows a simple IR receiver and sender circuit that uses the parts from the part list above. (a)Infrared Receiver and Sender circuit (b) Infrared Receiver and Sender circuit connections to Arduino UNO The required input is taken from the IR sensor by pointing the remote control of the device towards the IR sensor and pressing the required key to replicate , the Arduino will replicate the data and assign it to one of the switches. We may add as many switches as needed to implement many functions. And also an LED to indicate learning and use mode connected to pin 13. 

![alt text](https://github.com/Shivans-Awasthi/Custom-IR-based-Learning-Remote-control-using-Arduino/blob/main/circuit1.png?raw=true)
![alt text](https://github.com/Shivans-Awasthi/Custom-IR-based-Learning-Remote-control-using-Arduino/blob/main/circuit2.png?raw=true)


# V. IMPLIMENTATION AND RESULTS 
We can add a toggle or slide switch to power on the Arduino and the connect circuit, one of the push buttons is assign to switch between learning mode and use mode . When the learning button is pressed an indication is shown on the Arduino as well as the indicator LED as a long continuous glow, during this time the key to be learned is press from the device remote pointing to the IR receiver. The moment command is received from the remote the Arduino will process it and assign it to one of the circuit switches and the indicator LED stops glowing. This way we can add many functions to our learning remote control which can even be of different devices. Now the learning remote is ready to be used as an alternative remote control for all learned functions and will work on devices associated with it. The remote was tested on remote control speakers, air conditioners, and television on which the result found was positive.

# CONCLUSION 
Universal Learning remote was made with three replicated keys using Arduino, which uses infrared to communicate with its associated devices. Detailed study was done in concept understanding and its implementation. 

# REFERENCES
[1]http://www.edusoftmax.com/infrared.html 
[2]https://en.wikipedia.org/wiki/Arduino 
Link for IRremote Library: https://github.com/Arduino-IRremote/Arduino-IRremote 
