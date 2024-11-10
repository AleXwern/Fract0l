/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:41:36 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/10 22:55:05 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"

/*
** Determines what fractal is currently set and returns int ITER
** that is used to calculate color with frc_FRACTAL.
*/

int				frc_tricorn(s_fractal *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while ((z.real * z.real) + (z.imaginary * z.imaginary) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			-2.0 * z.imaginary * z.real + frc->c.real,
			(z.imaginary * z.imaginary) - (z.real * z.real) + frc->c.imaginary);
		iter++;
	}
	return (iter);
}

int				frc_mandelbrot(s_fractal *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while ((z.real * z.real) + (z.imaginary * z.imaginary) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			(z.real * z.real) - (z.imaginary * z.imaginary) + frc->c.real,
			2.0 * z.real * z.imaginary + frc->c.imaginary);
		iter++;
	}
	return (iter);
}

int				frc_bship(s_fractal *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while ((z.real * z.real) + (z.imaginary * z.imaginary) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			fabs((z.real * z.real) - (z.imaginary * z.imaginary) + frc->c.real),
			fabs(-2.0 * z.real * z.imaginary + frc->c.imaginary));
		iter++;
	}
	return (iter);
}

int				frc_julia(s_fractal *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while ((z.real * z.real) + (z.imaginary * z.imaginary) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			(z.real * z.real) - (z.imaginary * z.imaginary) + frc->jul.real,
			2.0 * z.real * z.imaginary + frc->jul.imaginary);
		iter++;
	}
	return (iter);
}
