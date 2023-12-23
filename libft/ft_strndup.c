/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:15:18 by akhossan          #+#    #+#             */
/*   Updated: 2019/11/17 21:11:58 by ayb*****         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t times)
{
	char	*dup;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (!(dup = ft_strnew(ft_strlen(s) * times)))
		return (NULL);
	i = 0;
	while (times--)
	{
		ft_memcpy(dup + i, s, len);
		i += len;
	}
	dup[++i] = 0;
	return (dup);
}
