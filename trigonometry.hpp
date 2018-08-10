#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include <math.h>

/**
 * @brief cosd Return the cosine of an angle specified in degrees.
 * @param angle Angle in degrees.
 * @return the cosine of the given angle.
 */
inline double cosd (int angle)
{
	return cos (angle * M_PI / 180);
}

/**
 * @brief sind Return the sine of an angle specified in degrees.
 * @param angle Angle in degrees.
 * @return the sine of the given angle.
 */
inline double sind (int angle)
{
	return sin (angle * M_PI / 180);
}

#endif // TRIGONOMETRY_H
