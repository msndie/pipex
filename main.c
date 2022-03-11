/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclam <sclam@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:11:46 by sclam             #+#    #+#             */
/*   Updated: 2021/11/07 19:06:00 by sclam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_from_file2_file(char **argv)
{
	int		fd1;
	int		fd2;
	char	c;

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
	{
		ft_putstr_fd("An error has occurred while open\n", 2);
		exit(EXIT_FAILURE);
	}
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		ft_putstr_fd("An error has occurred while open\n", 2);
		exit(EXIT_FAILURE);
	}
	while (read(fd1, &c, 1) > 0)
		write(fd2, &c, 1);
	close(fd1);
	close(fd2);
}

char	*ft_check_command(char **path, char **args)
{
	char	*command;
	char	*command2;
	int		i;

	i = 0;
	command = ft_strjoin("/", args[0]);
	if (!command)
		return (0);
	while (path[i])
	{
		command2 = ft_strjoin(path[i++], command);
		if (!command2)
			break ;
		if (access(command2, F_OK) == 0)
		{
			free(command);
			return (command2);
		}
		free(command2);
	}
	free(command);
	return (ft_strdup(args[0]));
}

char	**ft_path_cmds(char **envp, char **args1, char **args2)
{
	char	**path;
	char	**cmds;
	int		i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", ft_strlen("PATH=")))
		i++;
	path = ft_split(envp[i] + ft_strlen("PATH="), ':');
	if (!path)
		return (0);
	cmds = (char **)malloc(sizeof(char *) * 3);
	if (!cmds)
		return (ft_free_arr(path));
	cmds[0] = ft_check_command(path, args1);
	if (!cmds[0])
	{
		ft_free_arr(path);
		return (ft_free_arr(cmds));
	}
	cmds[1] = ft_check_command(path, args2);
	ft_free_arr(path);
	if (!cmds[1])
		return (ft_free_arr(cmds));
	cmds[2] = NULL;
	return (cmds);
}

int	ft_check_err(int argc, char **argv, char **envp)
{
	if (argc == 5 && access(argv[1], R_OK) == 0)
	{
		if (ft_strncmp("", argv[2], 1) == 0 && ft_strncmp("", argv[3], 1) == 0)
		{
			ft_from_file2_file(argv);
			exit(EXIT_SUCCESS);
		}
		if (ft_strncmp("", argv[2], 1) == 0 || ft_strncmp("", argv[3], 1) == 0)
		{
			ft_pipex_one_com(argv, envp);
			exit(EXIT_SUCCESS);
		}
		return (0);
	}
	else if (access(argv[1], R_OK) == -1 && argc == 5)
	{
		perror("access");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("This program takes 4 arguments, no more, no less\n", 2);
		return (-2);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**args1;
	char	**args2;
	char	**cmds;

	if (ft_check_err(argc, argv, envp) != 0)
		return (0);
	args1 = ft_split(argv[2], ' ');
	if (!args1)
		return (0);
	args2 = ft_split(argv[3], ' ');
	if (!args2)
	{
		ft_free_arr(args1);
		return (0);
	}
	cmds = ft_path_cmds(envp, args1, args2);
	if (!cmds)
	{
		ft_free_arr(args1);
		ft_free_arr(args2);
		return (0);
	}
	ft_pipex(argv, args1, args2, cmds);
	return (0);
}
