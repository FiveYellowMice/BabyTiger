#include <avr/pgmspace.h>
#include "texts.h"

namespace texts {

  const PROGMEM char month_january[] = "January";
  const PROGMEM char month_february[] = "February";
  const PROGMEM char month_march[] = "March";
  const PROGMEM char month_april[] = "April";
  const PROGMEM char month_may[] = "May";
  const PROGMEM char month_june[] = "June";
  const PROGMEM char month_july[] = "July";
  const PROGMEM char month_august[] = "August";
  const PROGMEM char month_september[] = "September";
  const PROGMEM char month_october[] = "October";
  const PROGMEM char month_november[] = "November";
  const PROGMEM char month_december[] = "December";

  const PROGMEM char *months[] = {
    month_january,
    month_february,
    month_march,
    month_april,
    month_may,
    month_june,
    month_july,
    month_august,
    month_september,
    month_october,
    month_november,
    month_december,
  };

  const PROGMEM char day_of_week_sunday[] = "Sunday";
  const PROGMEM char day_of_week_monday[] = "Monday";
  const PROGMEM char day_of_week_tuesday[] = "Tuesday";
  const PROGMEM char day_of_week_wednesday[] = "Wednesday";
  const PROGMEM char day_of_week_thursday[] = "Thursday";
  const PROGMEM char day_of_week_friday[] = "Friday";
  const PROGMEM char day_of_week_saturday[] = "Saturday";

  const PROGMEM char *days_of_week[] = {
    day_of_week_sunday,
    day_of_week_monday,
    day_of_week_tuesday,
    day_of_week_wednesday,
    day_of_week_thursday,
    day_of_week_friday,
    day_of_week_saturday,
  };

}