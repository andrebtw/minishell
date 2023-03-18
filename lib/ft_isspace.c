/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:05:10 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/17 23:05:14 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int character)
{
	if (character == ' ' || character == '\t' || character == '\n'
		|| character == '\v' || character == '\f' || character == '\r')
		return (1);
	return (0);
}
