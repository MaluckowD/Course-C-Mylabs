#include "./global.h"

Device *createDevice(DeviceType type)
{
  Device *device = (Device *)malloc(sizeof(Device));
  if (device == NULL)
  {
    printf("Memory allocation error!\n");
    exit(1);
  }
  device->type = type;
  device->stateFlags = 0;
  return device;
}

// Функция добавления устройства в массив
void addDevice(Device **arr, int *size, Device *device)
{
  *arr = (Device *)realloc(*arr, (*size + 1) * sizeof(Device));
  if (*arr == NULL)
  {
    printf("Ошибка выделения памяти!\n");
    exit(1);
  }
  (*arr)[*size] = *device;
  (*size)++;
}

// Функция удаления устройства из массива по индексу
void removeDevice(Device **arr, int *size, int index)
{
  if (index < 0 || index >= *size)
  {
    printf("Invalid index!\n");
    return;
  }
  for (int i = index; i < *size - 1; i++)
  {
    (*arr)[i] = (*arr)[i + 1];
  }
  *arr = (Device *)realloc(*arr, (*size - 1) * sizeof(Device));
  (*size)--;
}

// Функция обновления данных устройства по индексу
void updateDevice(Device *arr, int size, int index)
{
  if (index < 0 || index >= size)
  {
    printf("Invalid index!\n");
    return;
  }
  printf("Введите новые данные для устройства:\n");
  switch (arr[index].type)
  {
  case PHONE:
    printf("  OS: ");
    scanf("%s", arr[index].phone.OS);
    printf("  Количество камер: ");
    scanf("%d", &arr[index].phone.count_cameras);
    break;
  case COMPUTER:
    printf("  Количество ядер: ");
    scanf("%d", &arr[index].computer.count_cores);
    printf("  Объем RAM: ");
    scanf("%d", &arr[index].computer.count_RAM);
    break;
  case PRINTER:
    printf("  Количество цветов: ");
    scanf("%d", &arr[index].printer.count_colors);
    printf("  Тип принтера: ");
    scanf("%s", arr[index].printer.type_printer);
    break;
  default:
    printf("Неизвестный тип устройства.\n");
    break;
  }
  printf("  Состояние (введите комбинацию флагов 1 - ON, 2 - OFF, 4 - WIFI, 8 - BLUETOOTH, 16 - CHARGING): ");
  scanf("%u", &arr[index].stateFlags);
}

// Функция вывода информации о всех устройствах
void printDevices(Device *arr, int size)
{
  printf("Информация об устройствах:\n");
  for (int i = 0; i < size; i++)
  {
    printf("  Устройство %d:\n", i + 1);
    printf("    Тип: %d\n", arr[i].type);
    switch (arr[i].type)
    {
    case PHONE:
      printf("      OS: %s\n", arr[i].phone.OS);
      printf("      Количество камер: %d\n", arr[i].phone.count_cameras);
      break;
    case COMPUTER:
      printf("      Количество ядер: %d\n", arr[i].computer.count_cores);
      printf("      Объем RAM: %d\n", arr[i].computer.count_RAM);
      break;
    case PRINTER:
      printf("      Количество цветов: %d\n", arr[i].printer.count_colors);
      printf("      Тип принтера: %s\n", arr[i].printer.type_printer);
      break;
    default:
      printf("      Неизвестный тип устройства.\n");
      break;
    }
    printf("    Состояние: \n");
    if (arr[i].stateFlags & ON)
    {
      printf("      Включен\n");
    }
    if (arr[i].stateFlags & OFF)
    {
      printf("      Выключен\n");
    }
    if (arr[i].stateFlags & WIFI)
    {
      printf("      Wi-Fi включен\n");
    }
    if (arr[i].stateFlags & BLUETOOTH)
    {
      printf("      Bluetooth включен\n");
    }
    if (arr[i].stateFlags & CHARGING)
    {
      printf("      Заряжается\n");
    }
  }
}

// Функция вывода информации об устройствах с заданной комбинацией состояний
void printDevicesByState(Device *arr, int size, unsigned int stateMask)
{
  printf("Информация об устройствах с состоянием %u:\n", stateMask);
  for (int i = 0; i < size; i++)
  {
    if (arr[i].stateFlags & stateMask)
    {
      printf("  Устройство %d:\n", i + 1);
      printf("    Тип: %d\n", arr[i].type);
      switch (arr[i].type)
      {
      case PHONE:
        printf("      OS: %s\n", arr[i].phone.OS);
        printf("      Количество камер: %d\n", arr[i].phone.count_cameras);
        break;
      case COMPUTER:
        printf("      Количество ядер: %d\n", arr[i].computer.count_cores);
        printf("      Объем RAM: %d\n", arr[i].computer.count_RAM);
        break;
      case PRINTER:
        printf("      Количество цветов: %d\n", arr[i].printer.count_colors);
        printf("      Тип принтера: %s\n", arr[i].printer.type_printer);
        break;
      default:
        printf("      Неизвестный тип устройства.\n");
        break;
      }
      printf("    Состояние: \n");
      if (arr[i].stateFlags & ON)
      {
        printf("      Включен\n");
      }
      if (arr[i].stateFlags & OFF)
      {
        printf("      Выключен\n");
      }
      if (arr[i].stateFlags & WIFI)
      {
        printf("      Wi-Fi включен\n");
      }
      if (arr[i].stateFlags & BLUETOOTH)
      {
        printf("      Bluetooth включен\n");
      }
      if (arr[i].stateFlags & CHARGING)
      {
        printf("      Заряжается\n");
      }
    }
  }
}
