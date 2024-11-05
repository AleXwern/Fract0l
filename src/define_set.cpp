/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_set.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:41:36 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/05 21:31:20 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"

/*
** Determines what fractal is currently set and returns int ITER
** that is used to calculate color with frc_FRACTAL.
*/

static int	frc_tricorn(t_fractol *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while (pow(z.real, 2.0) + pow(z.imaginary, 2.0) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			-2.0 * z.imaginary * z.real + frc->c.real,
			pow(z.imaginary, 2.0) - pow(z.real, 2.0) + frc->c.imaginary);
		iter++;
	}
	return (iter);
}

static int	frc_mandelbrot(t_fractol *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while (pow(z.real, 2.0) + pow(z.imaginary, 2.0) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			pow(z.real, 2.0) - pow(z.imaginary, 2.0) + frc->c.real,
			2.0 * z.real * z.imaginary + frc->c.imaginary);
		iter++;
	}
	return (iter);
}

static int	frc_bship(t_fractol *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while (pow(z.real, 2.0) + pow(z.imaginary, 2.0) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			fabs(pow(z.real, 2.0) - pow(z.imaginary, 2.0) + frc->c.real),
			fabs(-2.0 * z.real * z.imaginary + frc->c.imaginary));
		iter++;
	}
	return (iter);
}

static int	frc_julia(t_fractol *frc)
{
	int			iter;
	t_complex	z;

	z = set_complex(frc->c.real, frc->c.imaginary);
	iter = 0;
	while (pow(z.real, 2.0) + pow(z.imaginary, 2.0) <= 4
		&& iter < frc->iter)
	{
		z = set_complex(
			pow(z.real, 2.0) - pow(z.imaginary, 2.0) + frc->jul.real,
			2.0 * z.real * z.imaginary + frc->jul.imaginary);
		iter++;
	}
	return (iter);
}

int			define_set(t_fractol *frc)
{
	switch (frc->fractol)
	{
	case 0:
		return frc_mandelbrot(frc);
	case 1:
		return frc_julia(frc);
	case 2:
		return frc_bship(frc);
	default:
		return frc_tricorn(frc);
	}
}
