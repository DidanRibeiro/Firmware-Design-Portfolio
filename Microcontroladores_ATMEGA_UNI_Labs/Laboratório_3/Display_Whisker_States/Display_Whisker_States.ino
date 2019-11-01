/*
 * Robotics with the BOE Shield - DisplayWhiskerStates
 * Display left and right whisker states in Serial Monitor.
 * 1 indicates no contact; 0 indicates contact.
 */

void setup()                                 // Built-in initialization block
{
  tone(10, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  pinMode(8, INPUT);                         // Set right whisker pin to input
  pinMode(9, INPUT);                         // Set left whisker pin to input  

  Serial.begin(9600);                        // Set data rate to 9600 bps
}  
 
void loop()                                  // Main loop auto-repeats
{                                            
  byte wLeft = digitalRead(8);               // Copy left result to wLeft  
  byte wRight = digitalRead(9);              // Copy right result to wRight

  Serial.print(wLeft);                       // Display left whisker state
  Serial.println(wRight);                    // Display right whisker state

  delay(50);                                 // Pause for 50 ms
}    
