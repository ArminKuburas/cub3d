/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:57:58 by akuburas          #+#    #+#             */
/*   Updated: 2024/08/09 00:09:59 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

double	rad_convert(double degrees)
{
	return (degrees * (M_PI / 180));
}

int	main(void)
{
	double	degrees;

	degrees = 30;

	printf("Degrees: %lf\n", degrees);
	printf("Radians: %lf\n", rad_convert(degrees));
	return (0);
}
