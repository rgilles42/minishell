/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_resolver_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 18:02:53 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/30 13:03:22 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

char	*evar_name(char *str, int just_count)
{
	int		i;

	i = 0;
	if (str[0] == '?' || ft_isdigit(str[0]))
		i = 1;
	if (!i)
		while (str[i] == '_' || ft_isalnum(str[i]))
			i++;
	if (just_count)
		return ((char *)(long)i);
	return (ft_substr(str, 0, i));
}

int	var_concat_before(char *current, char **new, int i)
{
	char	*tmp;
	char	*bvar;

	bvar = ft_substr(current, 0, i);
	if (!bvar)
		return (-1);
	tmp = *new;
	*new = ft_strjoin(*new, bvar);
	free(tmp);
	free(bvar);
	if (!*new)
		return (-1);
	return (0);
}

int	var_concat_supp(char *current, char **new, t_varenv *ve)
{
	char	*tmp;
	char	**bvar;
	char	*value;
	char	*name;

	name = evar_name(current, 0);
	bvar = var_value_finder(ve, name, 1);
	free(name);
	if (!bvar)
		return (0);
	value = bvar[0];
	tmp = *new;
	*new = ft_strjoin(*new, value);
	free(tmp);
	free(value);
	free(bvar);
	if (!*new)
		return (-1);
	return (0);
}

int	var_concat(char *current, char **new, t_varenv *ve, int next_var)
{
	int		i;

	i = next_var;
	if (var_concat_before(current, new, i) == -1)
		return (-1);
	if (!current[i])
		return (i);
	if (var_concat_supp(&current[i + 1], new, ve) == -1)
		return (-1);
	i += (long)evar_name(&current[i + 1], 1) + 1;
	return (i);
}
