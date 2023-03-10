/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:19:27 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/10 12:13:30 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEADER_H
# define HEADER_H

/* SYSTEM LIBS */
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

/* HEADER FILES */
# include "../lib/libft.h"

/* COLORS */
# define KNORMAL "\x1B[0m"
# define KRED "\x1B[31m"
# define KGREEN "\x1B[32m"
# define KYELLOW "\x1B[33m"
# define KBLUE "\x1B[34m"
# define KWHITE "\x1B[37m"

/* ERROR MESSAGES */


/* ERROR CODES */
# define ERR_MALLOC -2

#endif
