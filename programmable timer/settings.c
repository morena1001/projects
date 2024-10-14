#include "settings.h"
#include <stdio.h>

time_state* user_time;

void System_Init(void) {
	user_time = (time_state*) calloc(1, sizeof(time_state));

	user_time->hours = 0;
	user_time->minutes = 0;
	user_time->seconds = 0;

	user_time->hours_m = 0;
	user_time->minutes_m = 0;
	user_time->seconds_m = 0;
}

void Increment_User_Time(bool hour, bool minute, bool second){
	if (hour && user_time->hours < 23)		user_time->hours++;
	if (minute && user_time->minutes < 59)	user_time->minutes++;
	if (second && user_time->seconds < 59)	user_time->seconds++;
}

void Decrement_User_Time(bool hour, bool minute, bool second) {
	if (hour && user_time->hours > 0)		user_time->hours--;
	if (minute && user_time->minutes > 0)	user_time->minutes--;
	if (second && user_time-> seconds > 0)	user_time->seconds--;
}

void Clear_Time(bool memory_time) {
	if (memory_time) {
		user_time->hours_m = 0;
		user_time->minutes_m = 0;
		user_time->seconds_m = 0;
	}

	user_time->hours = 0;
	user_time->minutes = 0;
	user_time->seconds = 0;
}

void Set_Time(void) {
	if (__GET_MEMORY_TIME_IN_SECONDS == 0) {
		user_time->hours_m = user_time->hours;
		user_time->minutes_m = user_time->minutes;
		user_time->seconds_m = user_time->seconds;
	}
}

void Access_Memory_Time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
	*hours = user_time->hours_m;
	*minutes = user_time->minutes_m;
	*seconds = user_time->seconds_m;
}

char* Time_To_String(void) {
	char* output = malloc(sizeof(char) * 9);

	sprintf(output, "%d%d:%d%d:%d%d", 
		(uint8_t)(user_time->hours / 10), user_time->hours % 10,
		(uint8_t)(user_time->minutes / 10), user_time->minutes % 10,
		(uint8_t)(user_time->seconds / 10), user_time->seconds % 10);

	return output;
}

char* Memory_Time_To_String(void) {
	char* output = malloc(sizeof(char) * 9);

	sprintf(output, "%d%d:%d%d:%d%d", 
		(uint8_t)(user_time->hours_m / 10), user_time->hours_m % 10,
		(uint8_t)(user_time->minutes_m / 10), user_time->minutes_m % 10,
		(uint8_t)(user_time->seconds_m / 10), user_time->seconds_m % 10);

	return output;
}

void Countdown_Running(void) {
	if (user_time->seconds == 0) {
		user_time->seconds = 59;

		if (user_time->minutes == 0) {
			if (user_time->hours > 0) {
				user_time->hours--;
				user_time->minutes = 59;
			}
		} else {
			user_time->minutes--;
		}
	} else {
		user_time->seconds--;
	}
}
