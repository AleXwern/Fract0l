/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:24:47 by anystrom          #+#    #+#             */
/*   Updated: 2024/11/13 21:57:27 by AleXwern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALUE_H
# define VALUE_H
#pragma once

/*
** Error messages.
*/
#define G_ERROR		"General error happened. Exiting program."
#define B_ARG		"Error: Bad argument."
#define USAGE		"Usage:	./fractol mandelbrot/julia/bship/psecorn"
#define MEM_ERROR	"Not enough memory to allocate space for ./fractol."
#define T_ERROR		"There was a threading problem."
#define OOPS		"This should never be shown. Everyone panic!"
#define FINE		"Successfully exiting program."
#define WIN_ERROR	"Could not create a window."
#define IMG_ERROR	"Could not create a image."
#define MLX_ERROR	"Could not cleate MLX pointer."

/*
** Window size.
*/
constexpr uint32_t WINX = 720;
constexpr uint32_t WINY = 720;
constexpr uint32_t PIXELS = WINX * WINY;

/*
** Help data
*/
# define DATA		0x13D9EC
# define HL			0xff3333
# define HLP		"HELP"
# define HLP_A		"ESC    = exit"
# define HLP_B		"R      = reset"
# define HLP_C		"SPACE  = (un)anchor julia"
# define HLP_D		"D-PAD  = move"
# define HLP_E		"H      = open/close help"
# define HLP_F		"1234   = change factal"
# define HLP_G		"C      = change color"
# define HLP_H		"SCROLL = zoom in/out"
# define HLP_I		"/*     = add/remove threads"
# define HLP_J		"+-     = change iteration"
# define DATA_F		"Julia is fixed"
# define DATA_O		"Julia is not fixed"

#endif
