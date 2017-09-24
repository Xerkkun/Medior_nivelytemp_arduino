#include <TimerOne.h>
#include <LiquidCrystal.h> 
//Libreria para LCD

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
//Variables
int sonda = 12, termistor = 13;
unsigned long time1 = 0, time2 = 0, time3 = 0, time4 = 0;
int estado = 0, tiempo_alto1 = 0, tiempo_alto2 = 0;
float temperatura = 0, volumen = 0;

int lecturas1[30];
int lecturas2[30]; //Vector de datos
int n = 30;
int val,j = 0, i = 0, total1 = 0, total2 = 0, promedio1 = 0, promedio2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sonda, INPUT);
  pinMode(termistor, INPUT);
  
  lcd.begin(8, 2); //¿Modificar para pantalla de dos renglones?
  lcd.clear();

  //Refrescar valores en LCD cada 1 s
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(LCD) ;

  //Inicializar el vector
  for(i = 0; i < n; i++)
  lecturas1[i]=0;
  i=0;

  for(j = 0; j < n; j++)
    lecturas2[j]=0;
      j=0;
}

void loop() {
  //sustrae el total con la lectura inmediata anterior
  total1 = total1 - lecturas1[i];
  //llama la funcion que recopila las mediciones
  nivel();
  //guarda las mediciones en el vector
  lecturas1[i] = tiempo_alto1;
  //suma las lecturas
  total1 = total1 + lecturas1[i];
  i = i + 1;
  //calcular el promedio de las lecturas
  if(i >= n){
    i=0;
    promedio1 = total1/n;   
  conversion1();

  }
  //sustrae el total con la lectura inmediata anterior
  total2 = total2 - lecturas2[j];
  //llama la funcion que recopila las mediciones
  temp();
  //guarda las mediciones en el vector
  lecturas2[j] = tiempo_alto2;
  //suma las lecturas
  total2 = total2 + lecturas2[j];
  j = j + 1;
  //calcular el promedio de las lecturas
  if(j >= n){
    j=0;
    promedio2 = total2/n;   
  conversion2();

  }  

}
void nivel(){
  estado = digitalRead(sonda);
  while (estado == LOW){
    time1 = time1;
    estado = digitalRead(sonda);
  }
  if (estado == HIGH){
      time1 = micros();
      while (estado == HIGH){;
      time1=time1;
      estado = digitalRead(sonda);
      }
      if (estado == LOW){
        time2 = micros();
        estado = digitalRead(sonda);
      }
  }
  tiempo_alto1 = time2 - time1;
}

void temp(){
  estado = digitalRead(termistor);
  while (estado == LOW){
    time3 = time3;
    estado = digitalRead(termistor);
  }
  if (estado == HIGH){
      time3 = micros();
      while (estado == HIGH){;
      time3=time3;
      estado = digitalRead(termistor);
      }
      if (estado == LOW){
        time4 = micros();
        estado = digitalRead(termistor);
      }
  }
  tiempo_alto2 = time4 - time3;
}

void conversion1(){
  volumen = (promedio1-36.0285)/99.5277;
}

void conversion2(){
  temperatura = 129.335-(18.8738*log(promedio2-53.88));
}


void LCD() {
  lcd.clear();
  lcd.print("Vol = ");
  lcd.print(volumen);
  lcd.print(" lts");
  lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.print(temperatura);
  lcd.print(" C");
}


