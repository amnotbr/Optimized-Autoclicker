#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <ctype.h>



#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"



void clickMouse()
{
  static INPUT inputs[2] = {0};
  inputs[0].type = INPUT_MOUSE;
  inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  
  inputs[1].type = INPUT_MOUSE;
  inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
  SendInput(2, inputs, sizeof(INPUT));
}

int clickLoop(int off, int on)
{
  printf("RUNNING... O to run L to turn off\n");
  int onOff = 0; // initially set it to false (0)

  timeBeginPeriod(1);
  while (1)
  {
    if ((GetAsyncKeyState(off) & 0x8000) && (onOff == 0)) // set it to on (Letter O)
    {
      onOff = 1;
      system("cls");
      printf("Mouse click ON\n");
    }
    else if ((GetAsyncKeyState(on) & 0x8000) && (onOff == 1)) // set it off (letter L)
    {
      onOff = 0;
      system("cls");
      printf("Mouse click OFF\n");
    }
    if (onOff == 1)
    {
      clickMouse();
      Sleep(2);
    }
    else
    {
      Sleep(200);
    }
  }
  timeEndPeriod(1);
  
  return 0;
}

int convertLetterToHex(char off, char on)
{
  system("cls");
  char *offBuffer = (char *)malloc(5);
  char *onBuffer = (char *)malloc(5);

  int uppercaseOff = toupper(off);
  int uppercaseOn = toupper(on);
  
  snprintf(offBuffer, 5, "0x%X", uppercaseOff);
  snprintf(onBuffer, 5, "0x%X", uppercaseOn);

  //clickLoop(offBuff, onBuff);
  int numOff = (int)strtol(offBuffer, NULL, 0);
  int numOn = (int)strtol(onBuffer, NULL, 0);

  clickLoop(numOff, numOn);


  free(offBuffer);
  free(onBuffer);
}

int main()
{

  char *buffOne = (char *)malloc(3);
  char *buffTwo = (char *)malloc(3);

  // check if buffer allocations failed
  if (buffOne == NULL)
  {
    fprintf(stderr, "MEMORY ALLOCATION FAILED FOR BUFFER ONE");
    return 1;
  }
  if (buffTwo == NULL)
  {
    fprintf(stderr, "MEMORY ALLOCATION FAILED FOR BUFFER TWO");
    return 1;
  }


  printf("SETUP\n\n"); // title
  printf("Please enter the key to turn on the auto clicker: ");
  char *onKey = fgets(buffOne, 3, stdin);
  buffOne[strcspn(buffOne, "\n")] = '\0';

  puts("\n");
  printf("Please enter the key to turn off the autoclicker: ");
  char *offKey = fgets(buffTwo, 3, stdin); 
  buffTwo[strcspn(buffTwo, "\n")] = '\0';



  if(onKey == NULL)
  {
    fprintf(stderr, "ERROR");
    return 1;
  }
  else if(offKey == NULL)
  {
    fprintf(stderr, "ERROR");
    return 1;
  }

  convertLetterToHex(*onKey, *offKey);
  

  Sleep(200);
  free(buffOne);
  free(buffTwo);
}
