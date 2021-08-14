/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouchata <nouchata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 15:32:26 by nouchata          #+#    #+#             */
/*   Updated: 2021/08/13 21:03:03 by nouchata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int			builtin_export(t_execdata *d, t_varenv *ve);
t_envitem	**builtin_export_alphafinder(t_varenv *ve);
int			builtin_unset(t_execdata *d, t_varenv *ve);
int			builtin_envc(t_execdata *d, t_varenv *ve);
int			builtin_cd(t_execdata *d);
int			builtin_echo(t_execdata *d);
int			builtin_exit(void *minishell, char **str);
int			print_builtin(t_execdata *d, char *str);
int			builtin_dispatcher(t_execdata *d, t_varenv *ve);

#endif