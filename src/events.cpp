/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:01:55 by AleXwern          #+#    #+#             */
/*   Updated: 2024/11/05 21:42:59 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.hpp"

void	handle_keyboard(SDL_KeyboardEvent event, t_fractol *frc)
{
	if (event.state == SDL_PRESSED)
		return;
	switch (event.keysym.scancode)
	{
	case SDL_SCANCODE_ESCAPE:
		error_out("This is fine");
		return;
	case SDL_SCANCODE_F:
		frc->fractol = (frc->fractol + 1) % 4;
		return;
	case SDL_SCANCODE_C:
		frc->colourset = (frc->colourset + 1) % 3;
		return;
	default:
		return;
	}
}
