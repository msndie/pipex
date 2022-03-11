/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:30:23 by sclam             #+#    #+#             */
/*   Updated: 2021/12/12 21:23:45 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	while (i != 0)
		free(arr[--i]);
	free(arr);
	return (0);
}

void	ft_free_arrs(char **arr1, char **arr2, char **arr3, char *str)
{
	ft_free_arr(arr1);
	ft_free_arr(arr2);
	ft_free_arr(arr3);
	return (perror(str));
}

void	ft_child1(int *pipefd, char *cmd, char **args1, char **argv)
{
	int	fd;

	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("An error has occurred while open\n", 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	execve(cmd, args1, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	ft_child2(int *pipefd, char *cmd, char **args2, char **argv)
{
	int	fd;

	close(pipefd[1]);
	fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("An error has occurred while open\n", 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 1);
	dup2(pipefd[0], 0);
	close(fd);
	execve(cmd, args2, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	ft_pipex(char **argv, char **args1, char **args2, char **cmds)
{
	int		pipefd[2];
	pid_t	cpid1;
	pid_t	cpid2;

	if (pipe(pipefd) == -1)
		return (ft_free_arrs(cmds, args1, args2, "pipe"));
	cpid1 = fork();
	if (cpid1 == -1)
		return (ft_free_arrs(cmds, args1, args2, "fork"));
	if (cpid1 == 0)
		ft_child1(pipefd, cmds[0], args1, argv);
	cpid2 = fork();
	if (cpid2 == -1)
		return (ft_free_arrs(cmds, args1, args2, "fork"));
	if (cpid2 == 0)
		ft_child2(pipefd, cmds[1], args2, argv);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	ft_free_arr(cmds);
	ft_free_arr(args1);
	ft_free_arr(args2);
}
