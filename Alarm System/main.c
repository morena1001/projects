#include <stdio.h>

#include "alarm_system.h"

void check() {
    printf("%s\n", __GET_SYSTEM_STATE == set ? "set" : "ready");
}

bool update() {
    if (!Lock_System())     return Unlock_System();
    return true;
}

int main(int argc, char** argv) {
    char buffer[5];
    buffer[0] = '1';
    buffer[1] = '0';
    buffer[2] = '0';
    buffer[3] = '1';
    
    printf("_%s_\n", buffer);

    buffer[0] = '\0';
    printf("_%s_\n", buffer);
    
    // System_Init();

    // printf("%d  ", update());
    // check();
    // printf("%d  ", update());
    // check();

    // char buffer[5];
    // buffer[0] = '1';
    // buffer[1] = '0';
    // buffer[2] = '0';
    // buffer[3] = '1';
    // user_input = buffer;

    // printf("%d  ", update());
    // check();

    // printf("%d  ", update());
    // check();

    // printf("%d  ", Lock_System());
    // check();

    // printf("%d  ", Lock_System());
    // check();

    // printf("%d  ", Unlock_System());
    // check();

    // char buffer[5];

    // buffer[0] = '1';
    // buffer[1] = '0';
    // buffer[2] = '0';
    // buffer[3] = '2';

    // user_input = buffer;

    // printf("%d  ", Unlock_System());
    // check();

    // buffer[0] = '1';
    // buffer[1] = '0';
    // buffer[2] = '0';
    // buffer[3] = '1';

    // user_input = buffer;

    // printf("%d  ", Unlock_System());
    // check();

    // printf("%d  ", Unlock_System());
    // check();

    // printf("%d  ", Change_Password("2345"));
    // printf("%d\n", Check_Password());

    // printf("%d  ", Lock_System());
    // check();

    // printf("%d  ", Unlock_System());
    // check();



    return 0;
}
