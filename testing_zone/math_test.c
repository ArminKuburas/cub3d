/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:57:58 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/19 12:00:37 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

double	radian_converter(double degrees)
{
	return (degrees * (M_PI / 180));
}

int	main(void)
{
	double	degrees;

	degrees = 30;

	printf("Degrees: %lf\n", degrees);
	printf("Radians: %lf\n", radian_converter(degrees));
	return (0);
}
