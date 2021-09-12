/**
 * @file main.cpp
 * @author Adam Kuchto (adamkuchto@gmail.com)
 * @version 0.1
 * @date 2021-09-11
 * @copyright Copyright (c) 2021
 */

#include <Arduino.h>
#include "define.c"

int ledy[] = {9, 10, 11, 12};     // tablica pinów wyjściowych na ledy
int count = 0;                    // licznik kliknięć przycisku
int tonacja[] = {aa, bb, cc, dd}; // dzwięk na raz
int one = 0;                      // zmienna dla tonacja[]

void LedOn()
{
  /**
   * @brief Construct a new pin Mode object
   * funkcja inicjalizująca ledy
   */
  for (int i = 0; i < 4; i++)
  {
    pinMode(ledy[i], OUTPUT);
  }
}

int Switch()
{
  /**
   * @brief Construct a new if object
   * funkcja licząca ilość przyciśnięć buttona
   * @return count
   */
  int status = digitalRead(but1);
  if (status == HIGH)
  {
    count++;
    delay(150);
    if (count > 4)
    {
      count = 0;
    }
  }
  return count;
}

void master(int count, int r, int ton)
/**
 * @brief funkcja wykonawsza
 * włącza buzzer i ledy
 * @param count
 * @param r
 * @param ton
 */
{
  if (count == 1)
  {
    tone(buzz, tonacja[one], 16);
    digitalWrite(ledy[0], HIGH);
    delay(r);
    digitalWrite(buzz, LOW);
    digitalWrite(ledy[0], LOW);
    delay(r);
  }
  else if (count == 2)
  {

    tone(buzz, tonacja[one], 16);
    digitalWrite(ledy[0], HIGH);
    delay(r);
    digitalWrite(ledy[0], LOW);
    delay(r);

    tone(buzz, NOTE_C6, 16);
    digitalWrite(ledy[1], HIGH);
    delay(r);
    digitalWrite(ledy[1], LOW);
    delay(r);
  }
  else if (count == 3)
  {
    tone(buzz, tonacja[one], 16);
    digitalWrite(ledy[0], HIGH);
    delay(r);
    digitalWrite(ledy[0], LOW);
    delay(r);

    tone(buzz, NOTE_C6, 16);
    digitalWrite(ledy[1], HIGH);
    delay(r);
    digitalWrite(ledy[1], LOW);
    delay(r);

    tone(buzz, NOTE_C6, 16);
    digitalWrite(ledy[2], HIGH);
    delay(r);
    digitalWrite(ledy[2], LOW);
    delay(r);
  }
  else if (count == 4)
  {
    tone(buzz, tonacja[one], 16);
    digitalWrite(ledy[0], HIGH);
    delay(r);
    digitalWrite(ledy[0], LOW);
    delay(r);

    tone(buzz, NOTE_C6, 16);
    digitalWrite(ledy[1], HIGH);
    delay(r);
    digitalWrite(ledy[1], LOW);
    delay(r);

    tone(buzz, NOTE_C6, 16);
    digitalWrite(ledy[2], HIGH);
    delay(r);
    digitalWrite(ledy[2], LOW);
    delay(r);

    tone(buzz, NOTE_C6, 16);
    digitalWrite(ledy[3], HIGH);
    delay(r);
    digitalWrite(ledy[3], LOW);
    delay(r);
  }
  else
  {

    digitalWrite(buzz, LOW);
  }
}

void Print(int c, int res)
{
  /**
   * @brief Construct a new switch object
   * funkcja wyświetlająca informację o metrum 
   * @param c
   */
  switch (c)
  {
  case 1:
    Serial.print("1/4\n");
    Serial.print(res);
    break;
  case 2:
    Serial.print("2/4\n");
    Serial.print(res);
    break;
  case 3:
    Serial.print("3/4\n");
    Serial.print(res);
    break;
  case 4:
    Serial.print("4/4\n");
    Serial.print(res);
    break;

  default:
    Serial.print("Metronome by Adam Kuchto\n");
    break;
  }
}

int speed()
{
  /**
   * @brief tempo
   * funkcja do zmiany tempa poprzez potencjometr
   * @return resist
   */
  float resist = analogRead(A1);
  float bpm = ceil((60.000 / resist) * 1000);
  return bpm;
}

int beep()
{
  /**
   * @brief dzwięk
   * funkcja do zmiany brzmienia pierwszego uderzenia
   * @return one
   */
  int status = digitalRead(but2);
  if (status == HIGH)
  {
    one++;
    delay(150);
    if (one > 4)
    {
      one = 0;
    }
  }
  return one;
}

void setup()
{
  Serial.begin(9600);
  LedOn(); // inicjalzacja ledów

  pinMode(buzz, OUTPUT);       //buzzer
  pinMode(but1, INPUT_PULLUP); //button
}

void loop()
{
  speed();                        // tempo
  master(count, speed(), beep()); // główna funkcja buzzer + ledy
  Print(count, speed());          // funkcja wypisująca dane przez port szeregowy
  Switch();                       // funkcja licząca przyciśnięcia buttona
}
