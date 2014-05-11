#include <cstdio>
#include <vector>
using std::vector;

struct Date {
  Date(int year_in, int month_in, int day_in) {
    year = year_in;
    month = month_in;
    day = day_in;
  }
  int year;
  int month;
  int day;
};

const int kMonthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int KDaysOfWeek = 7;
enum YearDays {
  kNormYearDays = 365,
  kLeapYearDays = 366,
};

bool IsLeapYear(const int &year) {
  if ((year % 400 == 0) ||
      (((year % 4) == 0) && (year % 100) != 0)) {
    return true;
  } else {
    return false;
  }
}

int MonthDaysOfYear(int year, int month) {
  int days = kMonthDays[month];
  if (month == 2 && IsLeapYear(year)) {
    days++;
  }
  return days;
}

int DaysOfYear(const Date &date) {
  int days = 0;
  days += date.day;
  for (int i = 1; i < date.month; ++i) {
    days += MonthDaysOfYear(date.year, i);
  }
  return days;
}

int DaysBetween(const Date &date_pre, const Date &date_next) {
  int days = 0;
  for (int year_ = date_pre.year; year_ < date_next.year; ++year_) {
    days += (IsLeapYear(year_) ? kLeapYearDays : kNormYearDays);
  }
  days += DaysOfYear(date_next);
  days -= DaysOfYear(date_pre);
  return days;
}

void PrintCalendar(const vector<vector<int> > &calendar) {
  printf("Sun Mon Tue Wed Thu Fri Sat\n");
  int i;
  for (i = 0; i < KDaysOfWeek - calendar[0].size(); ++i) {
    printf("    ");
  }
  for (i = 0; i < calendar.size(); ++i) {
    for (int j = 0; j < calendar[i].size(); ++j) {
      printf("%-4d", calendar[i][j]);
    }
    printf("\n");
  }
}

int DayOfWeek(const Date &date) {
  const Date kFirstDate(1900, 1, 1);  // Mon
  return (DaysBetween(kFirstDate, date) % 7 + 1);
}

void CalendarOfMonth(int year, int month, vector<vector<int> > *calendar) {
  Date first_of_month(year, month, 1);
  int day_of_week = DayOfWeek(first_of_month);
  vector<int> temp;
  for (int i = 0; i < MonthDaysOfYear(year, month); ++i) {
    temp.push_back(i);
    if ((day_of_week + i) % KDaysOfWeek == 6) {
      calendar->push_back(temp);
      temp.clear();
    }
  }
  printf("Year:%d Month:%d\n", year, month);
  PrintCalendar(*calendar);
}

int main(int argc, char *argv[]) {
  Date date_prev(2014, 5, 1);
  Date date_next(2014, 6, 23);
  printf("%d\n", DaysBetween(date_prev, date_next));
  printf("%d\n", DayOfWeek(date_prev));
  vector<vector<int> > calendar;
  CalendarOfMonth(2014, 5, &calendar);
  return 0;
}
