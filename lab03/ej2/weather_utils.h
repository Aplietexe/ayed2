#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H
#include "array_helpers.h"
#include "weather.h"

/**
 * @brief Get the minimum temperature from the weather table
 * @param[in] a Weather table
 * @return Minimum temperature
 */
int get_minimum_temperature(WeatherTable a);

/**
 * @brief Compute the maximum temperature for each year
 * @param[in] a Weather table
 * @param[out] max_temp Array to store the maximum temperature for each year
 */
void compute_yearly_max_temperature(WeatherTable a, int max_temp[YEARS]);

/**
 * @brief Compute the rainiest month for each year
 * @param[in] a Weather table
 * @param[out] rainiest_month Array to store the rainiest month for each year
 */
void compute_yearly_rainiest_month(WeatherTable a,
                                   month_t rainiest_month[YEARS]);

#endif  //_WEATHER_UTILS_H
