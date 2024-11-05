#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

// Функция создания новой структуры устройства
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

int main()
{
  // Инициализация массива устройств
  Device *devices = NULL;
  int size = 0;

  // Главный цикл программы
  while (true)
  {
    printf("\nМеню:\n");
    printf("1. Добавить устройство\n");
    printf("2. Удалить устройство\n");
    printf("3. Обновить устройство\n");
    printf("4. Вывести все устройства\n");
    printf("5. Вывести устройства с заданным состоянием\n");
    printf("6. Выход\n");
    printf("Введите номер действия: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
      printf("Введите тип устройства (0 - Телефон, 1 - Компьютер, 2 - Принтер, 3 - Другое): ");
      int type;
      scanf("%d", &type);
      DeviceType deviceType = (DeviceType)type;
      Device *newDevice = createDevice(deviceType);
      switch (deviceType)
      {
      case PHONE:
        printf("  OS: ");
        scanf("%s", newDevice->phone.OS);
        printf("  Количество камер: ");
        scanf("%d", &newDevice->phone.count_cameras);
        break;
      case COMPUTER:
        printf("  Количество ядер: ");
        scanf("%d", &newDevice->computer.count_cores);
        printf("  Объем RAM: ");
        scanf("%d", &newDevice->computer.count_RAM);
        break;
      case PRINTER:
        printf("  Количество цветов: ");
        scanf("%d", &newDevice->printer.count_colors);
        printf("  Тип принтера: ");
        scanf("%s", newDevice->printer.type_printer);
        break;
      default:
        printf("Неизвестный тип устройства.\n");
        break;
      }
      printf("  Состояние (введите комбинацию флагов 1 - ON, 2 - OFF, 4 - WIFI, 8 - BLUETOOTH, 16 - CHARGING): ");
      scanf("%u", &newDevice->stateFlags);
      addDevice(&devices, &size, newDevice);
      break;
    }
    case 2:
    {
      if (size == 0)
      {
        printf("Массив пуст.\n");
        break;
      }
      printf("Введите индекс устройства для удаления: ");
      int index;
      scanf("%d", &index);
      removeDevice(&devices, &size, index - 1);
      break;
    }
    case 3:
    {
      if (size == 0)
      {
        printf("Массив пуст.\n");
        break;
      }
      printf("Введите индекс устройства для обновления: ");
      int index;
      scanf("%d", &index);
      updateDevice(devices, size, index - 1);
      break;
    }
    case 4:
    {
      if (size == 0)
      {
        printf("Массив пуст.\n");
        break;
      }
      printDevices(devices, size);
      break;
    }
    case 5:
    {
      if (size == 0)
      {
        printf("Массив пуст.\n");
        break;
      }
      printf("Состояние 1 - ON, 2 - OFF, 4 - WIFI, 8 - BLUETOOTH, 16 - CHARGING:\n");
      printf("Введите маску состояния (комбинацию флагов): ");
      unsigned int stateMask;
      scanf("%u", &stateMask);
      printDevicesByState(devices, size, stateMask);
      break;
    }
    case 6:
      printf("Выход из программы.\n");
      free(devices);
      return 0;
    default:
      printf("Некорректный выбор.\n");
    }
  }

  return 0;
}