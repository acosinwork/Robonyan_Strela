
String s[] = {
  "Здравствуй, Землянин. Я прилетел из другой галактики спасаясь от демонов.",
  "У нас на планете открылся портал в ад и все погибли. Остался только я - личинка техномозга.",
  "Родители упаковали меня в это яйцо, и кинули в сторону земли (гравитация у нас так себе).",
  "Ну вот я и прилетел, что бы разумное существо меня собрало по частям и возродило к жизни. Типа того"
};

int i = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial)
  {
    ;;
    }

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(300);
  Serial.println(s[0][i++]);

}