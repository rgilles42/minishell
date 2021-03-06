/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:56:33 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/08 13:53:11 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n)
		while (s1[i] && s2[i] && i < n - 1 \
			&& (unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
	if (!n)
		while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
			i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
