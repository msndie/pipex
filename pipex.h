/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:28:33 by sclam             #+#    #+#             */
/*   Updated: 2021/11/04 16:50:03 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include "libft/libft.h"

void	ft_from_file2_file(char **argv);
char	*ft_check_command(char **path, char **args);
char	**ft_path_cmds(char **envp, char **args1, char **args2);
int		ft_check_err(int argc, char **argv, char **envp);
void	*ft_free_arr(char **arr);
void	ft_free_arrs(char **arr1, char **arr2, char **arr3, char *str);
void	ft_child1(int *pipefd, char *cmd, char **args1, char **argv);
void	ft_child2(int *pipefd, char *cmd, char **args2, char **argv);
void	ft_pipex(char **argv, char **args1, char **args2, char **cmds);
char	*ft_path_cmd(char **envp, char **args);
void	ft_child(int *pipefd, char *cmd, char **args, char **argv);
void	ft_write2file(int *pipefd, char **argv);
char	**ft_args(char **argv);
void	ft_pipex_one_com(char **argv, char **envp);

#endif /*PIPEX_H*/