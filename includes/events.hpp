/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:22:56 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/10 00:42:19 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <SDL.h>

#include "fractol.hpp"

class	FractolEventHandler
{
public:
	FractolEventHandler(SDL_mutex *mutex, t_fractol *frc) :
		evMutex(mutex), evFrc(frc)
	{
	}

	int	eventThreadMain(void);

private:

	void	handle_keyboard(SDL_KeyboardEvent event, t_fractol *frc);
	void	handle_mouse(SDL_Event *event, t_fractol *frc);
	void	handle_mousewheel(SDL_MouseWheelEvent *event, t_fractol *frc);

	SDL_Event	events;
	SDL_mutex	*evMutex;
	t_fractol	*evFrc;
	t_complex	oldpos;
};
