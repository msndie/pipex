/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_one_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 21:12:35 by sclam             #+#    #+#             */
/*   Updated: 2021/11/04 15:31:26 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_path_cmd(char **envp, char **args)
{
	char	**path;
	char	*cmd;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", ft_strlen("PATH=")))
		i++;
	path = ft_split(envp[i] + ft_strlen("PATH="), ':');
	if (!path)
		return (0);
	cmd = ft_check_command(path, args);
	if (!cmd)
		return (ft_free_arr(path));
	ft_free_arr(path);
	return (cmd);
}

void	ft_child(int *pipefd, char *cmd, char **args, char **argv)
{
	int	fd;

	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "An error has occurred while open\n", 34);
		exit(EXIT_FAILURE);
	}
	dup2(fd, 0);
	dup2(pipefd[1], 1);
	execve(cmd, args, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	ft_write2file(int *pipefd, char **argv)
{
	int		fd;
	char	c;

	wait(NULL);
	close(pipefd[1]);
	fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "An error has occurred while open\n", 34);
		exit(EXIT_FAILURE);
	}
	while (read(pipefd[0], &c, 1) > 0)
		write(fd, &c, 1);
	close(fd);
	close(pipefd[0]);
}

char	**ft_args(char **argv)
{
	char	**args;

	if (ft_strncmp("", argv[2], 1) == 0)
		args = ft_split(argv[3], ' ');
	if (ft_strncmp("", argv[3], 1) == 0)
		args = ft_split(argv[2], ' ');
	if (!args)
		exit(EXIT_FAILURE);
	return (args);
}

void	ft_pipex_one_com(char **argv, char **envp)
{
	char	**args;
	int		pipefd[2];
	pid_t	cpid;
	char	*cmd;

	if (pipe(pipefd) == -1)
		return (perror("pipe"));
	args = ft_args(argv);
	cmd = ft_path_cmd(envp, args);
	if (!cmd)
	{
		ft_free_arr(args);
		exit(EXIT_FAILURE);
	}
	cpid = fork();
	if (cpid == -1)
	{
		ft_free_arr(args);
		return (perror("fork"));
	}
	if (cpid == 0)
		ft_child(pipefd, cmd, args, argv);
	ft_write2file(pipefd, argv);
	ft_free_arr(args);
	free(cmd);
}
