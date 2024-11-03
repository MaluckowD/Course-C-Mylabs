#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum type_device
{
  Telephone,
  computer,
  printer
} DeviceType;

struct Telephone_params{
  char OS;
  int count_cameras;
};

struct computer_params
{
  int count_cores;
  int count_RAM;
};

struct printer_params
{
  char type_printer;
  int count_colors;
};

struct Device {
  DeviceType type;
  union {
    struct Telephone_params telephone;
    struct computer_params computer;
    struct printer_params printer;
  };

  enum DeviceStateFlags
  {
    ON = 1,
    OFF = 2,
    WIFI = 4,
    BLUETOOTH = 8
  }DeviceStateFlags;
  unsigned int stateFlags;
};

int main(){
  struct Device pk;
  pk.type = computer;
  pk.computer.count_cores = 8;
  pk.computer.count_RAM = 128;
  pk.stateFlags = BLUETOOTH | WIFI | ON;

  printf("Компьютер:\n");
  printf("  Тип: %d\n", pk.type);
  printf("  Ядра: %d\n", pk.computer.count_cores);
  printf("  RAM: %d ГБ\n", pk.computer.count_RAM);
  printf("  Состояние: \n");
  if (pk.stateFlags & ON)
  {
    printf("    Включен\n");
  }
  else{
    printf("    Выключен\n");
  }
  
  if (pk.stateFlags & WIFI)
  {
    printf("    Wi-Fi включен\n");
  }
  else{
    printf("    Wi-Fi выключен\n");
  }
  if (pk.stateFlags & BLUETOOTH)
  {
    printf("    Bluetooth включен\n");
  }
  else{
    printf("    Bluetooth выключен\n");
  }

  return 0;
}