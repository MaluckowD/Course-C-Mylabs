#ifndef PROGECT
#define PROGECT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct Vector3d
{
  float x;
  float y;
  float z;
  bool norm;
} Vector3d;

// Перечисление для типов устройств
typedef enum DeviceType
{
  PHONE,
  COMPUTER,
  PRINTER,
  OTHER
} DeviceType;

// Структура для параметров телефона
typedef struct PhoneParams
{
  char OS[50];
  int count_cameras;
} PhoneParams;

// Структура для параметров компьютера
typedef struct ComputerParams
{
  int count_cores;
  int count_RAM;
} ComputerParams;

// Структура для параметров телевизора
typedef struct PrinterParams
{
  char type_printer[50];
  int count_colors;
} PrinterParams;

////////////
// Флаги для состояния устройства
typedef enum DeviceStateFlags
{
  ON = 1,
  OFF = 2,
  WIFI = 4,
  BLUETOOTH = 8,
  CHARGING = 16
} DeviceStateFlags;
//////////////////

// Структура Device
typedef struct Device
{
  DeviceType type; // Тип устройства
  union
  {
    PhoneParams phone;       // Параметры телефона
    ComputerParams computer; // Параметры компьютера
    PrinterParams printer;   // Параметры принтера
  };
  unsigned int stateFlags;
} Device;

Vector3d create_vector(float x, float y, float z);
Vector3d sum_vectors(const Vector3d *v1, const Vector3d *v2);
Vector3d difference_vectors(const Vector3d *v1, const Vector3d *v2);
double angle(const Vector3d *v1, const Vector3d *v2);
Vector3d vector_multiplication(const Vector3d *v1, const Vector3d *v2);
Vector3d projection_vector(const Vector3d *v1, const Vector3d *v2);
void normalization(Vector3d *v);
void print_vector(Vector3d v);

Device *createDevice(DeviceType type);
void addDevice(Device **arr, int *size, Device *device);
void removeDevice(Device **arr, int *size, int index);
void updateDevice(Device *arr, int size, int index);
void printDevices(Device *arr, int size);
void printDevicesByState(Device *arr, int size, unsigned int stateMask);

#endif
