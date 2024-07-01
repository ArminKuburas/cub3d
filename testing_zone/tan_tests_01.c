/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tan_tests_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:29:54 by akuburas          #+#    #+#             */
/*   Updated: 2024/07/01 12:07:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#define RADIAN 0.0174533

int	main(void)
{
	double	one;
	double	two;
	double	three;

	one = tan(-30 * RADIAN);
	two = tan(0 * RADIAN);
	three = tan(89 * RADIAN);
	printf("This is tan(-30 * RADIAN): %f\n", one);
	printf("This is tan(330 * RADIAN): %f\n", two);
	printf("This is Xa 64/tan(330 * RADIAN): %f\n", 64 / two);
	printf("This is Xa 64/tan(-30 * RADIAN): %f\n", 64 / one);
	printf("This is Xa 64/tan(30 * RADIAN): %f\n", 64 / tan(30 * RADIAN));
	printf("This is tan(130 * RADIAN): %f\n", three);
	printf("This is Xa 64/tan(130 * RADIAN): %f\n", 64 / three);
	return (0);
}