#include <IRremote.h>

#define RECORD_BTN 2
#define REPLICATE1 5
#define REPLICATE2 6
#define REPLICATE3 7
#define REPLICATE4 8
#define IR_RECEIVEPIN 4
#define RECORD_TIMEOUT 5000
#define BTN_DEBOUNCE 100
#define STATUS_LED 13

// These variables control the internal state of the Arduino
bool recording = false; // The record button was pressed and the operation did not time out yet
bool replicate = false; // One of the replication buttons was pressed

// These arrays contain data related to the buttons
// !!! IMPORTANT !!!
// The lengths of these arrays must match in order for this project to function
bool pressedButtons[4] = {true, true, true,true}; // All true because we use a pull-up (i.e. the button states are high when not pressed and get pulled low when pressed)
int buttons[4] = {REPLICATE1, REPLICATE2, REPLICATE3, REPLICATE4};
long lastPressTimes[4];

// These arrays contain the captured IR data
// !!! IMPORTANT !!!
// The lengths of these arrays must match in order for this project to function
// Furthermore, the lengths must also match the length of the buttons array from above
unsigned long int data[4] = {};
int len[4] = {};

// The next captured index will be assigned to this index
// Note that the starting value is -1 because the variable will be incremented before assigning a new value
int nextIndex = -1;

int numberOfButtons = 0;
int pattern = -1;
long recordingStarted = -1;
int timer;

IRrecv receiver(IR_RECEIVEPIN);
IRsend sender;

void setup()
{
  Serial.begin(9600);

  // Wait for the serial port to open
  while(!Serial)
  {  }

  // Calculate the number of entries in the buttons array
  numberOfButtons = sizeof(buttons) / sizeof(int);

  // Initialize the digital I/O pins
  pinMode(RECORD_BTN, INPUT_PULLUP);
  pinMode(REPLICATE1, INPUT_PULLUP);
  pinMode(REPLICATE2, INPUT_PULLUP);
  pinMode(REPLICATE3, INPUT_PULLUP);
  pinMode(REPLICATE4, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);

  // Attach an interrupt that will fire when the record button is pressed
  attachInterrupt(digitalPinToInterrupt(RECORD_BTN), recordPressed, FALLING);
}



void loop()
{
  for(int i = 0; i < numberOfButtons; i++)
  {
  if(buttonPressed(i))
  { 
    replicatePressed(i + 1);
    break;
  }
  }

  if(!replicate && recording && millis() < (recordingStarted + RECORD_TIMEOUT))
  {
  decode_results results;
  
  if (receiver.decode(&results))
  {  
    int i = (++nextIndex) % numberOfButtons;
   
    data[i] = results.value;
    len[i] = results.bits;

    Serial.println("RECORDING DONE!");
    Serial.print("CAPTURED ");
    Serial.print(results.bits);
    Serial.print(": ");
    Serial.print(results.value, HEX);
    Serial.print(" ON REPLICATE BUTTON ");
    Serial.println(i+1);
   
    recording = false;
  }
  }
  else if(recording)
  {  
  Serial.println("RECORD TIMEOUT. BUTTON ASSIGNMENT UNCHANGED!");
  recording = false;
  }
  digitalWrite(STATUS_LED, recording);
     
  }


  // Returns true when the push button with the given index is pressed
bool buttonPressed(int index)
{
  if(index < numberOfButtons && index >= 0)
  {
  bool currentState = digitalRead(buttons[index]);
  bool oldState = pressedButtons[index];
    
  if(currentState != oldState && millis() > lastPressTimes[index] + BTN_DEBOUNCE)
  {
    pressedButtons[index] = !pressedButtons[index];
    lastPressTimes[index] = millis();

    return (oldState == true && currentState == false);
  }
  }

  return false;
}

// Replicate a previously stored IR signal using the NEC protocol
void replicatePressed(int number)
{    
  if(!recording && !replicate && number > 0 && number <= numberOfButtons)
  {
  replicate = true;
    if(len[number-1]==12 || len[number-1]==15)
    {         for (int i = 0; i < 3; i++) 
              {
              sender.sendSony(data[number -1],len[number -1]);
              Serial.print("REPLICATED ");
              Serial.println(len[number - 1]);
              Serial.println(data[number - 1]);
              delay(40); 
              }
    }
    else if(len[number-1]==32)
        { 
          sender.sendNEC(data[number -1],len[number -1]);
            Serial.print("REPLICATED ");
            Serial.println(len[number - 1]);
            Serial.println(data[number - 1]);
        }
    else 
    {
      sender.sendNEC(data[number -1],len[number -1]);
        Serial.print("REPLICATED ");
        Serial.println(len[number - 1]);
        Serial.println(data[number - 1]);
    }

  replicate = false;
  }
}

// Callback for when the record button is pressed
void recordPressed()
{
  if(!recording && !replicate)
  {
  Serial.println("RECORD PRESSED");
    
  // Enable the IR receiver
  // This will also reset it, so that it's ready to receive another code right away
  receiver.enableIRIn();
 
  recording = true;
  recordingStarted = millis();
  }
}
