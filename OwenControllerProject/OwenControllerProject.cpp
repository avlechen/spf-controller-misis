// OwenControllerProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "owen_io.h"
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>


const int address = 16;

enum
{
  TEMP1 = 1,
  TEMP2 = 2,
  TEMP3 = 3,
  PRESSURE = 4,
} Chanels;

template <typename T>
T askUser(std::string& message)
{
  std::cout << message;

  T c;
  std::cin >> c;

  std::cout << std::endl;

  return c;
}


void printError()
{
  char errStr[LASTERRTOSTR_BUFFER_SIZE];

  LastErrToStr(errStr);

  std::cout << "Oшибка: " << errStr << std::endl;
}

void setupConnection()
{
	int port = 0;
	while (port < 1 || port > 256) {
		port = askUser<int>(std::string("¬ведите номер COM-порта (1 - 256): "));
	}

	int res = OpenPort(port - 1, spd_9600, prty_NONE, databits_8, stopbit_1, RS485CONV_MANUAL);

	if (res != ERR_OK) {
		std::cout << "ќшибка открыти€ порта.\n";
		return;
	}
}

void setTarget(float target, int chanel)
{
  if (ERR_OK != WriteStoredDotS(address, ADRTYPE_8BIT, "SP.LU", target, 3 * (chanel - 1))) {
    printError();
  }
}

float setTargertTemperature()
{
  float temperature = 0;
  while (temperature < 1) {
    temperature = askUser<float>(std::string("¬ведите температуру: "));
  }
  setTarget(temperature, TEMP1);
  setTarget(temperature, TEMP2);
  setTarget(temperature, TEMP3);

  return temperature;
}

void setTargetPressure(float pressure) {
  // recalculate pressure to curent
  setTarget(pressure, PRESSURE);
}

float getReading(int channel)
{
  float value = 0;
  int timestamp = 0;
  if (ERR_OK != ReadIEEE32(address + channel - 1, ADRTYPE_8BIT, "rEAd", value, timestamp, -1)) {
    printError();
  }
  return value;
}

float getTemperature() {
  float t1 = getReading(TEMP1);
  float t2 = getReading(TEMP1);
  float t3 = getReading(TEMP1);

  return (t1 + t2 + t3) / 3;
}

bool readyForForming(float targetTemperature, float delta)
{
  float t = getTemperature();
  return std::abs(targetTemperature - t) < delta;
}

void Form()
{
  std::string pathToSchedule;
  std::ifstream ifs;

  std::cin.ignore();
  while (pathToSchedule.empty() || !ifs.good()) {
    pathToSchedule.clear();
    std::cout << "”кажите путь к графику давлени€: ";
    char c;
    do {
      std::cin.get(c);
      pathToSchedule.push_back(c);
    } while (c != '\n');
    pathToSchedule.pop_back();
    ifs.open(pathToSchedule, std::ifstream::in);

    std::cout << pathToSchedule << std::endl;
    std::cout << ifs.good() << std::endl;
  }

  time_t start;
  time(&start);
  time_t now;
  while (ifs.good()) {
    float t = 0, value = 0;

    ifs >> t;
    ifs >> value;

    do {
      time(&now);
      Sleep(200);
    } while (now - start < t);

    std::cout << start << ", " << now << std::endl;
    std::cout << t << ", " << value << std::endl;
  }

  ifs.close();
}

int _tmain(int argc, _TCHAR* argv[])
{
  char*  locale = setlocale(LC_ALL, "Russian");
  setupConnection();
  float targetTemperature = setTargertTemperature();

  while (!readyForForming(targetTemperature, 10)) {
    Sleep(1000);
  }

  Form();

	return 0;
}

