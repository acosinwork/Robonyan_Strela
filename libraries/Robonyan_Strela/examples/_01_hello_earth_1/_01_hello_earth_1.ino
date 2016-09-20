void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  while (!Serial)
  {
    ;;
  }

  tone(12, 1000, 20);

  Serial.println("Greeing! My name is Roboguy, i'm from Crog-8.");
  Serial.println("What is your name?");

  while (!Serial.available())
  {
    ;;
  }
  tone(12, 1000, 20);

  String a = Serial.readString();

  Serial.print("Glad to meet you, ");
  Serial.print(a);
  Serial.println("!");
delay(1000);
  tone(12, 1000, 20);
  Serial.println("Please, tell to my friends about yourself on http://amperka.ru/");
  
delay(1000);
  tone(12, 1000, 20);
  Serial.println("Starting to play!!!");



}

void loop() {
  // put your main code here, to run repeatedly:


}
