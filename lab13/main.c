
#include "./global.h"

int main(){
  while (true){
    printf("\nМеню:\n");
    printf("1. Lab11\n");
    printf("2. Lab12\n");
    int global_choice;
    scanf("%d", &global_choice);

    switch(global_choice){
      case 1:
      {
        Vector3d a1 = create_vector(2, 2, 2, false);
        Vector3d a2 = create_vector(5, 12, 0, false);
        printf("vector a1:\n");
        print_vector(&a1);
        printf("vector a2:\n");
        print_vector(&a2);
        printf("vector a1 + a2:\n");
        Vector3d sum = sum_vectors(&a1, &a2);
        print_vector(&sum);
        printf("vector a1 - a2:\n");
        Vector3d def = difference_vectors(&a1, &a2);
        print_vector(&def);
        printf("the angle between the vectors in radians:\n");
        double res = angle(&a1, &a2);
        printf("%.2f\n", res);
        printf("vector product:\n");
        Vector3d mult = vector_multiplication(&a1, &a2);
        print_vector(&mult);
        printf("Projection of a vector a1 onto a vector a2:\n");
        Vector3d proj = projection_vector(&a1, &a2);
        print_vector(&proj);
        normalization(&a1);
        printf("The resulting vectors a1 and a2:\n");
        print_vector(&a1);
        print_vector(&a2);
        break;
      }
      case 2:
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
        break;
      }
      default:
        printf("Input correct num\n");

    }
  }

  return 0;
}