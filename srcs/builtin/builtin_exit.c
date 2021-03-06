/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:37:42 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/30 13:51:32 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	exit_error(t_minishell *m, char *src)
{
	write(2, "bash: exit: ", 12);
	write(2, src, ft_strlen(src));
	write(2, ": numeric argument required\n", 28);
	exec_killer(m->ed);
	exit(2);
}

char	atoi_exit(char *src, char *stock)
{
	int				i;
	int				neg;
	unsigned long	ret;

	i = -1;
	ret = 0;
	neg = 1;
	while (src[0] == ' ')
		src = &src[1];
	if (src[0] == '-')
	{
		neg = -1;
		src = &src[1];
	}
	while (src[++i] && (src[i] >= '0' && src[i] <= '9'))
		ret = ret * 10 + (src[i] - '0');
	*stock = ret * neg;
	if (!i || (src[i] && !(src[i] >= '0' && src[i] <= '9')) || i > 20)
		return (0);
	if ((neg == -1 && ret > (unsigned long)LONG_MIN) || \
	(neg == 1 && ret > 9223372036854775807))
		return (0);
	return (1);
}

int	blank_return(t_execdata *d)
{
	int			ret;
	t_execdata	*tmp;

	ret = 0;
	while (d)
	{
		tmp = d;
		while (tmp)
		{
			if (tmp->type == BUILTIN || tmp->type == BINARY)
				break ;
			tmp = tmp->next;
		}
		if (!ft_strncmp(tmp->cmd[0], "exit", 0))
			break ;
		ret = exec_ret(d);
		while (d && d->pipe_on)
			d = d->next;
		d = d->next;
	}
	return (ret);
}

int	builtin_exit(void *minishell, char **str)
{
	t_minishell		*m;
	char			ret;

	ret = 0;
	m = minishell;
	write(2, "exit\n", 5);
	if (str && str[0] && str[1])
		error_handler_p("exit: too many arguments\n", 1);
	varenv_kill(&m->ve);
	if (!str || !str[0])
	{
		ret = blank_return(m->ed);
		exec_killer(m->ed);
		exit(ret);
	}
	if (!atoi_exit(str[0], &ret))
		exit_error(m, str[0]);
	exec_killer(m->ed);
	exit(ret);
	return (0);
}

int	fork_exit(void *minishell, int ret)
{
	t_minishell		*m;

	m = minishell;
	varenv_kill(&m->ve);
	exec_killer(m->ed);
	exit(ret);
	return (0);
}
