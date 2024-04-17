#include "array_helpers.h"
#include "weather.h"

int get_minimum_temperature(WeatherTable a) {
    int min = a[0][0][0]._min_temp;
    for (unsigned year = 0; year < YEARS; ++year) {
        for (month_t month = january; month <= december; ++month) {
            for (unsigned day = 0; day < DAYS; ++day) {
                if (a[year][month][day]._min_temp < min) {
                    min = a[year][month][day]._min_temp;
                }
            }
        }
    }
    return min;
}

void compute_yearly_max_temperature(WeatherTable a, int max_temp[YEARS]) {
    for (unsigned year = 0; year < YEARS; ++year) {
        max_temp[year] = a[year][0][0]._max_temp;
        for (month_t month = january; month <= december; ++month) {
            for (unsigned day = 0; day < DAYS; ++day) {
                if (a[year][month][day]._max_temp > max_temp[year]) {
                    max_temp[year] = a[year][month][day]._max_temp;
                }
            }
        }
    }
}

void compute_yearly_rainiest_month(WeatherTable a,
                                   month_t rainiest_month[YEARS]) {
    for (unsigned year = 0; year < YEARS; ++year) {
        unsigned int max_rainfall = 0;
        rainiest_month[year] = january;
        for (month_t month = january; month <= december; ++month) {
            unsigned int rainfall = 0;
            for (unsigned day = 0; day < DAYS; ++day) {
                rainfall += a[year][month][day]._rainfall;
            }
            if (rainfall > max_rainfall) {
                max_rainfall = rainfall;
                rainiest_month[year] = month;
            }
        }
    }
}
