/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:08:48 by rgiambon          #+#    #+#             */
/*   Updated: 2024/08/15 11:24:21 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execution(char *cmd, char **env)
{
	char	**cmd_tab;
	char	*path;

	cmd_tab = create_cmd_tab(cmd);
	path = path_finder(cmd_tab[0], env);
	if (path == NULL)
	{
		ft_putstr_fd(cmd_tab[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_all(cmd_tab);
		exit(127);
	}
	if (execve(path, cmd_tab, env) == -1)
	{
		free(path);
		free(cmd_tab);
		perror("Execution failed");
		exit(126);
	}
	free(path);
	free_all(cmd_tab);
}

void	open_and_check(int argc, char *argv[], int *fd1, int *fd2)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		exit(1);
	}
	*fd1 = open(argv[1], O_RDONLY);
	if (*fd1 < 0)
	{
		perror("Error");
		exit(1);
	}
	*fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd2 < 0)
	{
		perror("Error");
		exit(1);
	}
}

void	child_process(char *cmd1, int file_fd, int *pipe_fds, char **env)
{
	dup2(file_fd, STDIN_FILENO);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[0]);
	execution(cmd1, env);
}

void	parent_process(char *cmd2, int file_fd, int *pipe_fds, char **env)
{
	int	child_status;

	wait(&child_status);
	dup2(file_fd, STDOUT_FILENO);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[1]);
	execution(cmd2, env);
}

int	main(int argc, char *argv[], char **env)
{
	int		fd_file1;
	int		fd_file2;
	int		pipe_fds[2];
	pid_t	id;

	open_and_check(argc, argv, &fd_file1, &fd_file2);
	if (pipe(pipe_fds) < 0)
	{
		perror("Pipe creation failed");
		exit(1);
	}
	id = fork();
	if (id == -1)
	{
		perror("Fork system call failed.");
		exit(1);
	}
	if (id == 0)
		child_process(argv[2], fd_file1, pipe_fds, env);
	else
		parent_process(argv[3], fd_file2, pipe_fds, env);
	return (0);
}
