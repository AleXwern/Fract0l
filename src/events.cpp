/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:01:55 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/05 23:25:58 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"
#include "value.hpp"
#include <stdio.h>

void			handle_keyboard(SDL_KeyboardEvent event, t_fractol *frc)
{
	int		direction;
	double	delta;
	
	if (event.state == SDL_PRESSED)
		return;
	
	#pragma GCC diagnostic push		// Disable GCC freaking out for not having every single key here
	#pragma GCC diagnostic ignored "-Wswitch"
	switch (event.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		error_out("This is fine");
		return;
	case SDL_SCANCODE_F:
		frc->fractol = (frc->fractol + 1) % 4;
		return;
	case SDL_SCANCODE_C:
		frc->colourset = (frc->colourset + 1) % 4;
		return;
	case SDL_SCANCODE_KP_PLUS:
		frc->iter = frc->iter+1 < 100 ? frc->iter+1 : 100;
		printf("Iteratiuns %d\n", frc->iter);
		return;
	case SDL_SCANCODE_KP_MINUS:
		frc->iter = frc->iter-1 > 1 ? frc->iter-1 : 1;
		printf("Iteratiuns %d\n", frc->iter);
		return;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_DOWN:
		direction = (event.keysym.scancode - 81) * 2 - 1;
		delta = frc->max.imaginary - frc->min.imaginary;
		frc->min.imaginary += delta * 0.05 * -direction;
		frc->max.imaginary += delta * 0.05 * -direction;
		return;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_RIGHT:
		direction = (event.keysym.scancode - 79) * 2 - 1;
		delta = frc->max.real - frc->min.real;
		frc->min.real += delta * 0.05 * direction;
		frc->max.real += delta * 0.05 * direction;
		return;
	case SDL_SCANCODE_R:
		set_default(frc);
	default:
		return;
	}
	#pragma GCC diagnostic pop
}

void	handle_mouse(SDL_MouseButtonEvent event, SDL_MouseMotionEvent position, t_fractol *frc)
{
	static bool			isPressed = false;
	static t_complex	oldpos;
	t_complex			delta;

	isPressed = event.button == 1 ? true : false;
	if (isPressed)
	{
		delta = {(frc->max.real - frc->min.real) * ((oldpos.real - position.x) / WINX),
				 (frc->max.imaginary - frc->min.imaginary) * ((oldpos.imaginary - position.y) / WINY)};
		frc->min.real += delta.real;
		frc->max.real += delta.real;
		frc->min.imaginary -= delta.imaginary;
		frc->max.imaginary -= delta.imaginary;
	}
	oldpos = {static_cast<double>(position.x), static_cast<double>(position.y)};
}
