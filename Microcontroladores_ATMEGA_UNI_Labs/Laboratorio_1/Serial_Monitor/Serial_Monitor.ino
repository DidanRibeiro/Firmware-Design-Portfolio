/* Lab 1 Example 1 */

#define MESSAGE_LEN 20

void setup() {

char message[MESSAGE_LEN];


Serial.begin(9600);
Serial.flush();

Serial.println("******************************");

sprintf(message, "Hello, World! \n");
Serial.write(message);

Serial.println("******************************");

}

void loop() {

}
