#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

int two = 1;

bool Lock_System() {
    if (two == 1)  {
        two = 2;
        return true;
    }
    return false;
}

int main() {
    double raw = 900.0;
    if (raw <= 1000.0 || !Lock_System())	{
        printf("YAY  ");
    }

    printf("%d\n", two);

}



// void why(int num, ...) {
//    va_list arg_list;
//    va_start(arg_list, num);
//    __int16 counter = (__int16) va_arg(arg_list, int);
//    if (counter > 453)   counter = 0;

//    printf("%d  %d\n", num, counter);
// }

// int main() {
//     why(1);
//     why(1, 453);

//     return 0;
// }



// // void Generate_Tone(bool enable, ...) {
// // 	va_list arg_list;
// // 	va_start(arg_list, enable);
// // 	uint16_t counter = (uint16_t) va_arg(arg_list, int);
// // 	if (counter == NULL)	counter = 0;

// // 	if (enable) {
// // 		__HAL_TIM_SET_AUTORELOAD(&htim1, ENABLE_BEEP * 2);
// // 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ENABLE_BEEP);
// // 	} else {
// // 		__HAL_TIM_SET_AUTORELOAD(&htim1, 0);
// // 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
// // 	}

// // 	buzzer_length_counter = counter;
// // }