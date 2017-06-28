/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:42:33 by lweinste          #+#    #+#             */
/*   Updated: 2017/06/28 12:13:48 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t n)
{
	int		m;

	m = -1;
	if (d > s)
		while (n--)
			((char*)d)[n] = ((char*)s)[n];
	else if (d < s)
		while (++m < (int)n)
			((char*)d)[m] = ((char*)s)[m];
	return (d);
}
