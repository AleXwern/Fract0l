/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:40:31 by anystrom          #+#    #+#             */
/*   Updated: 2024/10/24 21:22:48 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
# include "value.hpp"

/*
** A short function that modifies the amount of threads used.
** Thread amount must be between 1 and Window height in pixels.
*/

static void	mod_thread(int key, t_fractol *frc)
{
	if (key == SLASH)
		frc->threads--;
	else
		frc->threads++;
	if (frc->threads < 1)
		frc->threads = 1;
	if (frc->threads > 30)
		frc->threads = 30;
}

/*
** Changes fractal if 1-4 is pressed as well as the iteration
** if + or - is pressed as well as color scheme if C is pressed.
*/

static void	change_fractal(int key, t_fractol *frc)
{
	if (key == KEY_ONE)
		frc->fractol = 0;
	else if (key == KEY_TWO)
		frc->fractol = 1;
	else if (key == KEY_TRE)
		frc->fractol = 2;
	else if (key == KEY_FOU)
		frc->fractol = 3;
	else if (key == KEY_C)
		frc->color.set++;
	else if (key == NUM_PLU)
		frc->iter++;
	else if (key == NUM_MIN)
		frc->iter--;
	if (frc->color.set > 2)
		frc->color.set = 0;
}

/*
** DELTA is the difference between MIN and MAX.
** The image is moved 5% of this delta and movement is camera based.
*/

static void	arrow_key(int key, t_fractol *frc)
{
	t_complex	delta;

	delta = set_complex(frc->max.real - frc->min.real, frc->max.imaginary - frc->min.imaginary);
	if (key == UP)
	{
		frc->min.imaginary += (delta.imaginary * 0.05);
		frc->max.imaginary += (delta.imaginary * 0.05);
	}
	else if (key == DOWN)
	{
		frc->min.imaginary -= (delta.imaginary * 0.05);
		frc->max.imaginary -= (delta.imaginary * 0.05);
	}
	else if (key == LEFT)
	{
		frc->min.real -= (delta.imaginary * 0.05);
		frc->max.real -= (delta.imaginary * 0.05);
	}
	else if (key == RIGHT)
	{
		frc->min.real += (delta.imaginary * 0.05);
		frc->max.real += (delta.imaginary * 0.05);
	}
}

/*
** Happens when keyboard is pressed.
** Keys are explained separately.
** Anyway, clears the window, draws a new one.
*/

int			key_main(int key, t_fractol *frc)
{
	if (key == ESC)
		error_out(FINE);
	else if (key == SCR_UPH)
		frc->ishelp = (frc->ishelp * frc->ishelp) - 1;
	else if (key == SPACE)
		frc->fixjulia = (frc->fixjulia * frc->fixjulia) - 1;
	else if (key == KEY_R)
		set_default(frc);
	else if (key >= 123 && key <= 126)
		arrow_key(key, frc);
	else if ((key >= 18 && key <= 21) || key == 8 || key == 69 || key == 78)
		change_fractal(key, frc);
	else if (key == 75 || key == 67)
		mod_thread(key, frc);
	//mlx_clear_window(frc->mlx, frc->win);
	thread_core(frc);
	return (0);
}
