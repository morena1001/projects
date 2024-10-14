#include <stdio.h>

#include "settings.h"

void printer(void) {
    printf("%d  %d\n", __GET_USER_TIME_IN_SECONDS, __GET_MEMORY_TIME_IN_SECONDS);
}

int main() {
    System_Init();
    
    for (int i = 0; i < 2; i++)     Increment_User_Time(1, 1, 0);
    for (int i = 0; i < 15; i++)    Increment_User_Time(0, 0, 1);
    printf("%s\n", Time_To_String());

    while (__GET_USER_TIME_IN_SECONDS > 0) {
        // if (user_time->seconds == 0) {
        //     user_time->seconds = 59;

        //     if (user_time->minutes == 0) {
        //         if (user_time->hours > 0) {
        //             user_time->hours--;
        //             user_time->minutes = 59;
        //         }
        //     } else {
        //         user_time->minutes--;
        //     }
        // } else {
        //     user_time->seconds--;
        // }
        Countdown_Running();
        printf("%s\n", Time_To_String());
    }
    // printf("%s\n", Time_To_String());

    
    
    
    
    // System_Init();
    // printf("%s\n", Time_To_String());
    // printf("%s\n\n", Memory_Time_To_String());

    // for (int i = 0; i < 3; i++)     Increment_User_Time(1, 0, 0);
    // for (int i = 0; i < 2; i++)     Increment_User_Time(0, 1, 0);
    // for (int i = 0; i < 25; i++)    Increment_User_Time(0, 0, 1);
    // printf("%s\n", Time_To_String());
    // printf("%s\n\n", Memory_Time_To_String());

    // Set_Time();
    // printf("%s\n", Time_To_String());
    // printf("%s\n\n", Memory_Time_To_String());

    // Clear_Time(false);
    // printf("%s\n", Time_To_String());
    // printf("%s\n\n", Memory_Time_To_String());

    // for (int i = 0; i < 30; i++)     Increment_User_Time(1, 0, 0);
    // for (int i = 0; i < 65; i++)     Increment_User_Time(0, 1, 0);
    // for (int i = 0; i < 65; i++)     Increment_User_Time(0, 0, 1);
    // printf("%s\n", Time_To_String());
    // printf("%s\n\n", Memory_Time_To_String());

    // for (int i = 0; i < 30; i++)     Decrement_User_Time(1, 0, 0);
    // for (int i = 0; i < 65; i++)     Decrement_User_Time(0, 1, 0);
    // for (int i = 0; i < 65; i++)     Decrement_User_Time(0, 0, 1);
    // printf("%s\n", Time_To_String());
    // printf("%s\n\n", Memory_Time_To_String());


    // System_Init();
    // // printer();

    // for (int i = 0; i < 3; i++)     Increment_User_Time(1, 0, 0);
    // for (int i = 0; i < 2; i++)     Increment_User_Time(0, 1, 0);
    // for (int i = 0; i < 25; i++)    Increment_User_Time(0, 0, 1);
    // printer();

    // Decrement_User_Time(0, 1, 0);
    // printer();

    // Set_Time();
    // printer();

    // Clear_Time(false);
    // printer();

    // for (int i = 0; i < 25; i++)    Increment_User_Time(0, 0, 1);
    // printer();

    // Set_Time();
    // printer();

    // Clear_Time(true);
    // printer();

    // Set_Time();
    // printer();

    // uint8_t hours, minutes, seconds;
    
    // Access_Memory_Time(&hours, &minutes, &seconds);

    // printf("%d  %d  %d\n", hours, minutes, seconds);

    // Clear_Time(false);
    // printer();
    // for (int i = 0; i < 25; i++)    printf("%d  ", __INCREMENT_SECONDS);
    

    return 0;
}

