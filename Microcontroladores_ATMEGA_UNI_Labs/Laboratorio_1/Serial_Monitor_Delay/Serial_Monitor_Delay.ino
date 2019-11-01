/* Lab 1 Example 1 */

#define MESSAGE_LEN 20

void setup() {
  

}

void loop() {

char message[MESSAGE_LEN];


Serial.begin(9600);
Serial.flush();

sprintf(message, "Hello, World! \n");
Serial.write(message);
delay(1000);

}
