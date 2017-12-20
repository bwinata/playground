#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
/* TESLA MOTORS FIRMWARE TEST
 * You have 90 minutes to complete the test.  Any answers given after 90 minutes
 * count significantly less towards the total score. There are 9 questions
 * ordered from lowest point value to highest.
 *
 * Do not use outside aid or share the content of this test
 *
 * All solutions should work in coderpad and can be compiled and run in Coderpad.io
 *
 * A main() function is provided at the bottom for your use
 */
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// 1) Celestial Body Struct
////////////////////////////////////////////////////////////////////////////////
// celestialBody_s is a data structure that represents celestial bodies in the
// solar system. However, the data structure is taking up too much space on
// an x86 system (32-bit aligned). How can the celestialBody_s structure be
// changed so that it needs 8 or fewer bytes for storage without losing fidelity
// in any of the members. Solutions that do not meet this requirement in
// coderpad will be considered incorrect.

// INCORRECT STRUCTURE
// typedef struct s_celestialBody {
//     uint8_t  zenithAngle;
//     uint32_t mass;
//     uint8_t  azimuthAngle;
//     uint16_t distanceFromEarth;
// } celestialBody_s;

typedef struct s_celestialBody {
        uint32_t mass;
        uint8_t  zenithAngle;
        uint8_t  azimuthAngle;
        uint16_t distanceFromEarths;
} celestialBody_s;

////////////////////////////////////////////////////////////////////////////////
// 2) Function-like macro
////////////////////////////////////////////////////////////////////////////////
// Suppose the compiler you are using does not support inline functions
// Write a function-like macro INCREMENT to increment a variable by an
// arbitrary amount. Both the variable to increment and the increment
// amount should be passed in as parameters.

#define INCREMENT(val, amount) ((val)+(amount))

////////////////////////////////////////////////////////////////////////////////
// 3) Array pointer math
////////////////////////////////////////////////////////////////////////////////
//
// Write some code in the arrayMath() function to print out the values located at:
// row 0, column 0
// row 1, column 2
// row 2, column 2
// You are not allowed to use [] to reference the elements of the array.
// You are only allowed to use pointers.
// There should be no compiler warnings or errors.
//
int myArray[3][4] =
{
    {0, 3, 6, 9},
    {1, 4, 7, 10},
    {15, 5, 20, 11}
};

void arrayMath()
{
  int row = 0, col = 0;

  int num_total = (int)(sizeof (myArray) / sizeof (**myArray));
  int num_cols  = (int)(sizeof (*myArray) / sizeof (myArray[0][0]));
  int num_rows  = num_total / num_cols;

  printf ("Total number of items = %d\n", num_total);
  printf ("No. of cols = %d\n", num_cols);
  printf ("No. of rows = %d\n", num_total / num_cols);

  printf ("Row = 0; Col = 0; Value = %d\n", **(myArray));
  printf ("Row = 1; Col = 2; Value = %d\n", *(*(myArray+1)+2));
  printf ("Row = 2; Col = 2; Value = %d\n", *(*(myArray+2)+2));
}

////////////////////////////////////////////////////////////////////////////////
// 4) Periodic Tasks
////////////////////////////////////////////////////////////////////////////////
//
// Assume there are two periodic tasks in the system. They run every 10ms and
// 100ms. The system starts up in main, which then creates the two tasks. Main
// is not shown here.
// Assume that the 100ms task is running at lower priority than the 10ms task.
// When the 10ms task needs to run, it interrupts the 100ms task, executes,
// and then returns control to the 100ms task.
// Please explain what is wrong with this code.
//

volatile int componentValue = 1;
int finalValue = 1;

void task_100ms()
{
    finalValue = componentValue * 2;
    sleep(50);

    if(finalValue == (componentValue * 2))
    {
        printf("finalValue is: %d", finalValue);
        printf("componentValue is : %d", componentValue);
    }
}

void task_10ms()
{
    componentValue += 1;
    if(componentValue > 20)
    {
        componentValue = 0;
    }
}
/* PLEASE PUT YOUR ANSWER HERE

finalValue is not declared as a volatile variable. This action tells the compiler to optimise the code for said variable. In turn, it will always be set to 1 in this case. Meaning, that the if condition in task_100ms will never be invoked.
 *
 *
 */

////////////////////////////////////////////////////////////////////////////////
// 5) Struct pointer math
////////////////////////////////////////////////////////////////////////////////
//
// Write some code in the structMath() function to print out the values for
// keyValue and alternateKeyValue from the Tesla laptop definition without using
// the '.' or '->' operators to directly reference the qwerty struct or its
// members.
// There should be no compiler warnings or errors.
//
typedef enum
{
    MOUSE_NONE,
    MOUSE_UP,
    MOUSE_DOWN,
    MOUSE_LEFT,
    MOUSE_RIGHT,
} mouse_direction_E;

typedef struct
{
    bool leftButton;
    bool rightButton;
    bool middleButton;
    bool mouseOn;
    mouse_direction_E direction;
} mouse_S;

typedef struct
{
    char keyValue;
    char alternateKeyValue;
} keyboard_S;

typedef struct
{
    mouse_S simpleMouse;
    keyboard_S qwerty;
} laptop_S;

laptop_S tesla =
{
    .simpleMouse =
    {
        .leftButton = false,
        .rightButton = false,
        .middleButton = false,
        .mouseOn = false,
        .direction = MOUSE_NONE,
    },
    .qwerty =
    {
        .keyValue = '5',
        .alternateKeyValue = '%'
    },
};

void structMath()
{
    // Cast to pointer
   // (char *) &(char *)&tesla
   printf ("Size of tesla keyboard structure = %d\n", (int)sizeof (tesla));
   printf ("Key value = %c\n", *(char *)((char *)&tesla + sizeof (mouse_S)));
   printf ("Alternate Key Value = %c\n", *(char *)((char *)&tesla + sizeof (mouse_S) + sizeof (char)));
}

////////////////////////////////////////////////////////////////////////////////
// 6) Hysteresis
////////////////////////////////////////////////////////////////////////////////
//
// heatingRequired
//
//  This function indicates whether heating is required to maintain a set
//  temperature, based on the current heater request state (initially off),
//  specified set temperature and the current tempareture.  The implementation
//  should have 1 degree of hysteresis around the set temperature to prevent
//  excessive toggling of the heater.  I.e., If the heater is already on, it
//  shall stay on within the range of [setTemp - 1 degC, setTemp + 1 degC].
//
//  arguments:
//   setTempHalfDeg - The set temperature in half-degree increments
//   curTempHalfDeg - The current temperature in half-degree increments
//
//  returns:
//   boolean indicating whether or not the heater should be active
//
bool heatingRequired(int16_t setTempHalfDeg, int16_t curTempHalfDeg)
{
    // Turn on heater since the current temp is less than the reference
    if (curTempHalfDeg < setTempHalfDeg - 1) return true;

    // Turn off heater since the current temp is more than the reference
    if (curTempHalfDeg > setTempHalfDeg + 1) return false;

    return true; // Else return true to ensure it stays within range
}

////////////////////////////////////////////////////////////////////////////////
// 7) Nibble Swap
////////////////////////////////////////////////////////////////////////////////
// The messaging protocol used by certain vehicle controllers requires that all
// nibbles in data payloads be swapped (e.g. 0x1234 -> 0x2143). Write a function
// that takes an unsigned 64-bit integer and swaps the nibbles like so:
// 0x0123456789ABCDEF to 0x1032547698BADCFE. The function should be independent
// of machine endianess.

uint64_t payload_nibble_swap(uint64_t p)
{
    uint64_t nibbleSwappedVal = 0;
    uint8_t sample = 0;

    uint8_t i = 0;
    uint8_t len = sizeof (p);

    while (i < len) {
      sample = p >> (i * 8);

      // Swap nibbles around in  sample
      sample = (sample & 0x0F) << 4 | (sample & 0xF0) >> 4;

      // Place swapped nibbles into variable
      nibbleSwappedVal = nibbleSwappedVal | (uint64_t) sample << (i * 8);

      i++;
    }

    return nibbleSwappedVal;
}

////////////////////////////////////////////////////////////////////////////////
// 8a) Braking Check
////////////////////////////////////////////////////////////////////////////////
// Design an input checker for a function that is used in an extremely safety
// critical braking system. This function takes two arguments, a pointer
// to a memory location that contains the distance to an obstacle in meters and
// a signed integer that is the closure rate in m/s.
//
// Implement the functions brakes_checkPointerAddr() and
// brakes_checkPointerData() so that the data used by the emergency braking
// calculation is guaranteed to be safe.
//

/*
 * @param distancePtr - int32_t pointer to data to be used
 *
 * returns true if pointer is non-NULL, 4 byte aligned
 * and in the range 0x1000 to 0xF000, false otherwise
 */
bool brakes_checkPointerAddr(int32_t* distancePtr)
{
    bool retVal = false;

    if (distancePtr == NULL) return retVal;

    if (((int64_t)distancePtr % 4) != 0) return retVal;

    if (*distancePtr < 0x1000 || *distancePtr > 0xF000) return retVal;

    // If the program gets here, it means that all validation / checks have passed
    // and the distance is within bounds and non-NULL
    retVal = true;

    return retVal;
}

/*
 * @param distancePtr - int32_t pointer to data to be used (guaranteed to be non-NULL)
 *
 * returns true if data value is positive, non-zero and not
 * equal to the sentinel value 0x7FFFFFFF, false otherwise
 */
bool brakes_checkPointerData(int32_t* distancePtr)
{
    bool retVal = false;

    if (distancePtr == NULL) return retVal;

    if (*distancePtr <= 0) return retVal;

    if (*distancePtr == 0x7FFFFFFF) return retVal;

    retVal = true;

    return retVal;
}

#define CLOSURE_RATE_THRESH 20U
#define DISTANCE_THRESH 100

/*
 * @param distancePtr - int32_t pointer to data to be used
 * @param closureRate - int32_t variable with the current closure rate in m/s
 *
 * returns TRUE if input data is valid and less than the
 * DISTANCE_THRESH constant and the closureRate is greater than the
 * CLOSURE_RATE_THRESH, FALSE otherwise
 */
bool brakes_activateEmergencyBraking(int32_t* distancePtr, int32_t closureRate)
{
    bool activateBrakes = false;
    if (brakes_checkPointerAddr(distancePtr))
    {
        if (brakes_checkPointerData(distancePtr))
        {
            if ((*distancePtr < DISTANCE_THRESH) && (closureRate > CLOSURE_RATE_THRESH))
            {
                activateBrakes = true;
            }
        }
    }
    return activateBrakes;
}

////////////////////////////////////////////////////////////////////////////////
// 8b) Braking Check Part 2
////////////////////////////////////////////////////////////////////////////////
//
// While testing the implementation for brakes_activateEmergencyBraking() above,
// an engineer discovered that there were cases where the closureRate was below
// the threshold, but an event was triggered.  Please explain what could have
// gone wrong and why.
//
// The closureRate variable could of overflowed. If the car was driving exceedingly high then the upper bounds of the closure rate would of rolled over, resetting itselfwhich would be less than the threshold.
//

////////////////////////////////////////////////////////////////////////////////
// 9) State Machine
////////////////////////////////////////////////////////////////////////////////
//
// Write a function to implement the state machine shown in the diagram below.
//  * The initial state of the state machine should be A
//  * State machine input is provided as an argument to the function
//  * The function should output the current state of the state machine
//
//
//     Input = 1   +---------+   Input = 4
//   +------------>|         |<------------+
//   |             | State A |             |
//   |  Input = 2  |         |  Input = 3  |
//   |   +-------- +---------+ --------+   |
//   |   |                             |   |
//   |   V                             V   |
// +---------+      Input = 6      +---------+
// |         |<--------------------|         |
// | State C |                     | State B |
// |         |-------------------->|         |
// +---------+      Input = 5      +---------+
//
//                                 +---------+
//              Input =            |         |
//              Unexpected Value   |  FAULT  |
//             +------------------>|         |
//                                 +---------+
//

typedef enum {
  STATE_A,
  STATE_B,
  STATE_C,
  FAULT,
} state;

state state_machine (int input)
{
  static state s = STATE_A;

  switch (s) {
    case STATE_A:
      switch (input) {
        case 2:
          s = STATE_C;
          break;
        case 3:
          s = STATE_B;
          break;
        default:
          return FAULT;
      }
      break;
    case STATE_B:
      switch (input) {
        case 4:
          s = STATE_A;
          break;
        case 6:
          s = STATE_C;
          break;
        default:
          return FAULT;
      }
      break;
    case STATE_C:
      switch (input) {
        case 1:
          s = STATE_A;
          break;
        case 5:
          s = STATE_B;
          break;
        default:
          return FAULT;
      }
      break;
    default:
      printf ("Error - System should not be in this state: %d\n", s);
  }

  return s;
}

////////////////////////////////////////////////////////////////////////////////
// Use this main to test your code
// All solutions should work in coderpad
////////////////////////////////////////////////////////////////////////////////
int main()
{

// 3 - 2D Array access via pointers

    arrayMath ();

//
    structMath ();

// 7 - Payload nibble swap
    uint64_t swapped_nibble = payload_nibble_swap (0x0123456789ABCDEF);
    assert (swapped_nibble == 0x1032547698BADCFE);

// 9 - State Machine
    assert (state_machine (3) == STATE_B);
    assert (state_machine (3) == FAULT);
    assert (state_machine (6) == STATE_C);


    return 0;
}
