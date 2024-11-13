/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:01:55 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/13 22:06:02 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.hpp"
#include "fractol.hpp"
#include "value.hpp"
#include <stdio.h>

int			FractolEventHandler::eventThreadMain(void)
{
	if (SDL_WaitEventTimeout(&events, 10))
	{
		SDL_LockMutex(evMutex);
		switch (events.type)
		{
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_KEY_UP:
			handle_keyboard(events.key);
			break;
		case SDL_EVENT_MOUSE_MOTION:
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_UP:
			handle_mouse(&events);
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			handle_mousewheel(&events.wheel);
			break;
		case SDL_EVENT_QUIT:
			error_out("This is fine");
			break;
		default:
			break;
		}
		SDL_UnlockMutex(evMutex);
	}
	return 1;
}

void		FractolEventHandler::handle_keyboard(SDL_KeyboardEvent event)
{
	int		direction;
	double	delta;
	
	if (event.down)
		return;
	
	#pragma GCC diagnostic push		// Disable GCC freaking out for not having every single key here
	#pragma GCC diagnostic ignored "-Wswitch"
	switch (event.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		error_out("This is fine");
		break;
	case SDL_SCANCODE_F:
		evFrc->fractol = (evFrc->fractol + 1) % 4;
		break;
	case SDL_SCANCODE_C:
		evFrc->colourset = (evFrc->colourset + 1) % 4;
		break;
	case SDL_SCANCODE_KP_PLUS:
		evFractal->iter++;
		printf("Iterations %d\n", evFractal->iter);
		break;
	case SDL_SCANCODE_KP_MINUS:
		evFractal->iter--;
		printf("Iterations %d\n", evFractal->iter);
		break;
	case SDL_SCANCODE_UP:
	case SDL_SCANCODE_DOWN:
		direction = (event.scancode - 81) * 2 - 1;
		delta = evFractal->max.imaginary - evFractal->min.imaginary;
		evFractal->min.imaginary += delta * 0.05 * -direction;
		evFractal->max.imaginary += delta * 0.05 * -direction;
		break;
	case SDL_SCANCODE_LEFT:
	case SDL_SCANCODE_RIGHT:
		direction = (event.scancode - 79) * 2 - 1;
		delta = evFractal->max.real - evFractal->min.real;
		evFractal->min.real += delta * 0.05 * direction;
		evFractal->max.real += delta * 0.05 * direction;
		break;
	case SDL_SCANCODE_R:
		set_default(evFrc);
		setDefaultFractalValues(evFractal);
		break;
	case SDL_SCANCODE_E:
		evFractal->iter = 0xffff;
		printf("Iterations %d\n", evFractal->iter);
		break;
	case SDL_SCANCODE_J:
		evFrc->fixjulia = evFrc->fixjulia ? false : true;
		break;
	case SDL_SCANCODE_1:
	case SDL_SCANCODE_2:
	case SDL_SCANCODE_3:
	case SDL_SCANCODE_4:
	case SDL_SCANCODE_5:
	case SDL_SCANCODE_6:
	case SDL_SCANCODE_7:
	case SDL_SCANCODE_8:
	case SDL_SCANCODE_9:
	case SDL_SCANCODE_0:
		evFractal->iter = (event.scancode - 29) * 10;
		printf("Iterations %d\n", evFractal->iter);
		break;
	default:
		break;
	}
	#pragma GCC diagnostic pop
}

void	FractolEventHandler::handle_mouse(SDL_Event *event)
{
	static bool			isPressed = false;
	t_complex			delta;

	isPressed = event->button.button == 1 ? true : false;
	if (isPressed)
	{
		delta = {(evFractal->max.real - evFractal->min.real) * ((oldpos.real - event->motion.x) / WINX),
				 (evFractal->max.imaginary - evFractal->min.imaginary) * ((oldpos.imaginary - event->motion.y) / WINY)};
		evFractal->min.real += delta.real;
		evFractal->max.real += delta.real;
		evFractal->min.imaginary -= delta.imaginary;
		evFractal->max.imaginary -= delta.imaginary;
	}
	if (evFrc->fixjulia)
	{
		evFractal->jul = set_complex(4 * ((double)event->motion.x / WINX - 0.5),
								4 * ((double)(WINY - event->motion.x) / WINY - 0.5));
	}
	oldpos = {static_cast<double>(event->motion.x), static_cast<double>(event->motion.y)};
}

void	FractolEventHandler::handle_mousewheel(SDL_MouseWheelEvent *event)
{
	double		zoom;
	t_complex	target;

	if (event->y > 0)
		zoom = 1.0 * 0.9;
	else
		zoom = 1.0 / 0.9;
	target = {1.00 * oldpos.real / (WINX / (evFractal->max.real - evFractal->min.real)) + evFractal->min.real,
			-1.0 * oldpos.imaginary / (WINY / (evFractal->max.imaginary - evFractal->min.imaginary)) + evFractal->max.imaginary};
	evFractal->min.real = ((evFractal->min.real - target.real) * zoom) + target.real;
	evFractal->min.imaginary = ((evFractal->min.imaginary - target.imaginary) * zoom) + target.imaginary;
	evFractal->max.real = ((evFractal->max.real - target.real) * zoom) + target.real;
	evFractal->max.imaginary = ((evFractal->max.imaginary - target.imaginary) * zoom) + target.imaginary;
}
