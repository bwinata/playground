#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static char GPS_output[] = "$GPRMC,173202.000,A,3722.8899,N,12159.5208,W,0.04,215.36,121017,,,A*7F";

typedef unsigned char bool;

static bool false = 0;
static bool true  = 1;

/// ----------------------------------------------------------------------------

static int gps_parse_str_time (struct tm * datetime, char * time)
{
  char * _time = NULL;
  char hms[2]  = {0};

  char * pch = strtok (time, ".");
  while (pch != NULL) {
    _time = pch;
    pch = strtok (NULL, ".");
  }
  printf ("GPS Time = %s\n", time);

  if (strlen (time) != 6) return -1;

  strncpy (hms, time, 2);
  datetime->tm_hour = atoi (hms);
  strncpy (hms, &time[2], 2);
  datetime->tm_min = atoi (hms);
  strncpy (hms, &time[4], 2);
  datetime->tm_sec = atoi (hms);

  return 0;
}

/// ----------------------------------------------------------------------------

static int gps_parse_str_date (struct tm * datetime, char * date)
{
  char dmy[2] = {0};

  printf ("GPS Date = %s\n", date);

  if (strlen (date) != 6) return -1;

  strncpy (dmy, date, 2);
  datetime->tm_mday = atoi (dmy) - 1;
  strncpy (dmy, &date[2], 2);
  datetime->tm_mon  = atoi (dmy) - 1;
  strncpy (dmy, &date[4], 2);
  datetime->tm_year = (atoi (dmy) + 2000) - 1900;

  return 0;
}

void gps_parse_datetime (struct tm * datetime, char * time, char * date)
{
  gps_parse_str_time (datetime, time);
  gps_parse_str_date (datetime, date);
}

/// ----------------------------------------------------------------------------
/// -- Entry Point
/// ----------------------------------------------------------------------------
int main (int argc, char ** argv)
{
  char * gprmc     = NULL;
  char * timestamp = NULL;
  char * datestamp = NULL;

  if ((gprmc = strstr (GPS_output, "$GPRMC"))) {
    int count = 0;
    char * pch = strtok (gprmc, ",");

    while (pch != NULL) {
      switch (count) {
        case 1:
            timestamp = pch;
          break;
        case 2:
            if (*pch == 'A') {
            } else {
              printf ("Error: GPRMC data is invalid\n");
              return -1;
            }
          break;
        case 9:
          datestamp = pch;
          break;
      }
      pch = strtok (NULL, ",");
      count++;
    }

    struct tm datetime;
    gps_parse_datetime (&datetime, timestamp, datestamp);

    time_t epoch = mktime (&datetime);
    printf ("Epoch = %ld\n", epoch);


  } else {
    printf ("Error: Cannot find GPRMC fields\n");
    return -1;
  }

  return 0;
}
