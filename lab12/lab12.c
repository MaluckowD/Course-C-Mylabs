#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

enum type_device
{
  Telephone,
  computer,
  printer
};

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
  enum type_device type;
  union {
    struct Telephone_params telephone;
    struct computer_params computer;
    struct printer_params printer;
  };
};

int main(){


  return 0;
}