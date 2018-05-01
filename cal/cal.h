#define TRUE 1
#define FALSE 0

#define CAL_WIDTH 20
#define WEEK_DAYS 7

int isLeapYear(int year) {
  /**
   * Algorithm for determining a leap year:
   * http://en.wikipedia.org/wiki/Leap_year
   */
  if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
    return TRUE;
  } else return FALSE;
}

int getDaysOfMonth(int month, int year) {
  int days = month % 7 % 2 == 1 ? 31 : 30;

  if (month == 2 /* Month is February */) {
    if (isLeapYear(year)) days = 29;
    else days = 28;
  }

  return days;
}

int getStartDay(int month, int year) {
  /**
   * Algorithm for computing day of Gregorian Calendar:
   * https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html
   */
  int startDay;
  int century = (int) year / 100;
  year = month < 3 ? (year - (century * 100)) - 1 : (year - (century * 100)); // rolls if months are jan or feb
  month = month < 3 ? month + 10 : month - 2; // rolls over the month

  startDay = (
    1 +
    ((int) (2.6 * month - 0.2)) -
    (2 * century) +
    year +
    ((int) year / 4) +
    ((int) century / 4)
  ) % WEEK_DAYS;

  return startDay < 0 ? WEEK_DAYS + startDay : startDay;
}

void printMonth(int month) {
  char *months[12] = {
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };
  int i, pad = (int) (CAL_WIDTH - strlen(months[month - 1])) / 2;

  // Print left pad
  for (i = 0; i < pad; i++) printf(" ");

  printf("%s", months[month - 1]);

  // Print right pad
  for (i = 0; i < CAL_WIDTH - (pad + strlen(months[month - 1])); i++) printf(" ");
}

void cal(int month, int year) {
  int startDay = getStartDay(month, year);
  int space, day;

  printMonth(month);
  printf("\n");

  // Print days of the week
  printf("Su Mo Tu We Th Fr Sa\n");

  // Print padded space
  for (space = 0; space < startDay; space++) printf("   ");

  // Print days
  for (day = 1; day < getDaysOfMonth(month, year) + 1; day++, startDay++) {
    if (day < 10) printf(" ");
    printf("%i ", day);
    if ((startDay + 1) % 7 == 0) printf("\n");
  }

  printf("\n");
}