/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcontent_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 16:56:07 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/27 10:57:57 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../minishell.h"

int	cmdcontent_io_transfert(t_cmdcontent *curr, char **cmds, int i)
{
	if (!cmds[i + 1])
		return (error_syntax_handler(cmds[i], 0, -1));
	if (!ft_strncmp(cmds[i + 1], "<", 1) || \
	!ft_strncmp(cmds[i + 1], "<<", 1) || \
	!ft_strncmp(cmds[i + 1], ">", 1) || \
	!ft_strncmp(cmds[i + 1], ">>", 1))
		return (error_syntax_handler(cmds[i], 0, -1));
	if (ioitem_builder(curr, cmds[i], cmds[i + 1]) == -1)
		return (-1);
	free(cmds[i]);
	cmds[i] = NULL;
	free(cmds[i + 1]);
	cmds[i + 1] = NULL;
	return (0);
}

int	cmdcontent_extract_iothings(t_cmdcontent *ccon, t_chunkseg *cs)
{
	int		i;

	i = 0;
	while (i < cs->segs_count)
	{
		if (cs->segments[i] && (!ft_strncmp(cs->segments[i], "<", 1) || \
		!ft_strncmp(cs->segments[i], "<<", 1) || \
		!ft_strncmp(cs->segments[i], ">", 1) || \
		!ft_strncmp(cs->segments[i], ">>", 1)))
		{
			if (cmdcontent_io_transfert(ccon, cs->segments, i) == -1)
				return (-1);
			i = 0;
			continue ;
		}
		i++;
	}
	return (0);
}

int	cmdc_ext_cmd_supp(t_chunkseg **cs, char ***cmd, int i, int *y)
{
	if ((*cs)->segments[i])
	{
		(*cmd)[*y] = ft_strdup((*cs)->segments[i]);
		if (!(*cmd)[*y])
		{
			*cmd = kill_segments(*cmd, 0);
			return (error_handler(NULL, NULL, -1));
		}
		free((*cs)->segments[i]);
		(*cs)->segments[i] = NULL;
		(*y)++;
	}
	return (0);
}

int	cmdcontent_extract_cmd(t_cmdcontent *ccon, t_chunkseg *cs)
{
	char	**cmd;
	int		i;
	int		y;
	int		ret;

	i = -1;
	y = count_strs(cs->segments, cs->segs_count);
	cmd = malloc(sizeof(char *) * (y + 1));
	if (!cmd)
		return (error_handler(NULL, NULL, -1));
	ft_memset(cmd, 0, sizeof(char *) * (y + 1));
	y = 0;
	while (++i < cs->segs_count)
	{
		ret = cmdc_ext_cmd_supp(&cs, &cmd, i, &y);
		if (ret)
			return (ret);
	}
	ccon->cmd = cmd;
	return (0);
}
