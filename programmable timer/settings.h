// INCLUDES
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// DEFINES
#define ENABLE_BEEP             1761
#define DISABLE_BEEP            0

#define INPUT_BEEP_LENGTH       83 // 165
#define ALARM_BEEP_LENGTH       28 // 41
#define ALARM_SILENT_LENGTH     227 // 453

// PRIVATE VARIABLES
typedef struct Time_State time_state;
extern time_state* user_time;

struct Time_State {
    uint8_t hours, minutes, seconds;
    uint8_t hours_m, minutes_m, seconds_m;
};

// MACROS
#define __GET_USER_TIME_IN_SECONDS         ((int)(user_time->hours) * 3600) + ((int)(user_time->minutes) * 60) + ((int)(user_time->seconds))
#define __GET_MEMORY_TIME_IN_SECONDS       ((int)(user_time->hours_m) * 3600) + ((int)(user_time->minutes_m) * 60) + ((int)(user_time->seconds_m))

#define __INCREMENT_HOURS       user_time->hours < 23 ? ++user_time->hours : user_time->hours
#define __INCREMENT_MINUTES     user_time->minutes < 59 ? ++user_time->minutes : user_time->minutes
#define __INCREMENT_SECONDS     user_time->seconds < 59 ? ++user_time->seconds : user_time->seconds

#define __DECREMENT_HOURS       user_time->hours > 0 ? --user_time->hours : user_time->hours
#define __DECREMENT_MINUTES     user_time->minutes > 0 ? --user_time->minutes : user_time->minutes
#define __DECREMENT_SECONDS     user_time->seconds > 0 ? --user_time->seconds : user_time->seconds

// FUNCTION PROTOTYPES
void System_Init(void);
void Increment_User_Time(bool hour, bool minute, bool second);
void Decrement_User_Time(bool hour, bool minute, bool second);
void Clear_Time(bool memory_time);
void Set_Time(void);
void Access_Memory_Time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

char* Time_To_String(void);
char* Memory_Time_To_String(void);

void Countdown_Running(void); 
