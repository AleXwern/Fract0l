/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mou_input.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:52:04 by anystrom          #+#    #+#             */
/*   Updated: 2024/10/24 21:23:15 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
# include "value.hpp"

/*
** Author's comment "Pain in the ass"
** "Dealigns" the image with MPOS modifier, modifies the image with
** zoom modifier so that the image is enlarged based on O-point and then
** "Re-alighns" the image back to original position.
** This makes the zoom anchor into mouse pos.
*/

static void	zoom(int key, t_fractol *frc, t_complex mpos)
{
	if (key == SCR_UPH)
		frc->zoom = 1.0 * 0.9;
	if (key == SCR_DOWN)
		frc->zoom = 1.0 / 0.9;
	frc->min.real = ((frc->min.real - mpos.real) * frc->zoom) + mpos.real;
	frc->min.imaginary = ((frc->min.imaginary - mpos.imaginary) * frc->zoom) + mpos.imaginary;
	frc->max.real = ((frc->max.real - mpos.real) * frc->zoom) + mpos.real;
	frc->max.imaginary = ((frc->max.imaginary - mpos.imaginary) * frc->zoom) + mpos.imaginary;
}

/*
** Actions when mouse buttons are pressed (complete, not half)
** MPOS is an modifier used later that calculates how much image
** needs to be de/re-aligned for the zoom to zoom correctly.
*/

int			mouse_main(int key, int x, int y, t_fractol *frc)
{
	t_complex	mpos;

	mpos.real = 1.00 * x / (WINX / (frc->max.real - frc->min.real)) + frc->min.real;
	mpos.imaginary = -1.0 * y / (WINY / (frc->max.imaginary - frc->min.imaginary)) + frc->max.imaginary;
	if (key == SCR_DOWN || key == SCR_UPH)
		zoom(key, frc, mpos);
	//mlx_clear_window(frc->mlx, frc->win);
	thread_core(frc);
	return (0);
}

/*
** Happens when mouse is moved.
** If fractal is julia and it's set to move, calculates a new mod
** to calculate Julia and then redraws it.
** Basically JUL ranges from -2+-2i to 2+2i when mouse is in 0-0
** to WINX-WINY respectively.
*/

int			julia_move(int x, int y, t_fractol *frc)
{
	if (frc->fixjulia && frc->fractol == 1)
	{
		frc->jul = set_complex(4 * ((double)x / WINX - 0.5),
			4 * ((double)(WINY - y) / WINY - 0.5));
		//mlx_clear_window(frc->mlx, frc->win);
		thread_core(frc);
	}
	return (0);
}
