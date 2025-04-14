#include "header.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int again = 1, countParkingLot;
    infoParking* parking;
    while(again)
    {
        while (again)
        {
            printf("\033[1;35mВведите количество автостоянок: \033[0m");
            countParkingLot = enterEl();
            parking = mem(countParkingLot);
            enterInfoParking(parking, countParkingLot);
            managerInfoCars(&parking, &countParkingLot);
            printf("\nХотите ввести данные о парковках снова? \033[32mДа - 1\033[0m. \033[31mНет - 0 \033[0m:\t");
            again = againProg();
        }
        memClear(parking, countParkingLot);
        printf("\nХотите запустить программу заново? \033[32mДа - 1\033[0m. \033[31mНет - 0 \033[0m:\t");
        again = againProg();
    }
    
    return 0;
}
