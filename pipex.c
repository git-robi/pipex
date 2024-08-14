/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:08:48 by rgiambon          #+#    #+#             */
/*   Updated: 2024/08/14 13:41:35 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*path_finder(char *cmd, char **envp)
{
	int	i;
	char	*start_ptr;
	char	**all_path;
	char	*path;

	i = 0;
	while(envp[i] != NULL)
	{
		if(ft_strnstr((const char) envp[i], (const char) "PATH=", 5) != 0)
		{
			start_ptr = envp[i] + 5;
			break;
		}
		i++;
	}
	//check for finding path error
	all_path = ft_split(start_ptr, ':');
	i = 0;
	while(all_path[i] != 0)
	{
		path = malloc(ft_strlen(all_path[i]) + ft_strlen(cmd) + 2);
		ft_strlcpy(path, (const char *)all_path[i], ft_strlen(path));
		ft_strcat(path, '/'); // add size
		ft_strlcat(path, cmd);
		if (access(path, X_OK) == 0)
		{
			free_all(all_path);
			return (path);
		}
		free(path);
		i++;
	}
	free_all(all_path);
	return (0);
}



void	*execution(char *cmd, char **envp)
{
	char	**cmd_tab;
	char	*path;

	cmd_tab = ft_split(cmd, ' ');
	path = path_finder(cmd_tab[0], envp);
	
	
}


void	open_and_check(int argc, char *argv[], int *fd1, int *fd2)
{	
	if (argc != 5)
	{
		write(2, "Error: wrong number of arguments", 32);
		exit(EXIT_FAILURE);
	}
	*fd1 = open(argv[1], O_RDONLY);
	if(*fd1 < 0)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	*fd2 = open(argv[4], O_WRONLY | O_CREATE | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		perror("Error opening file2");
		exit(EXIT_FAILURE);
	}
}

void	child_process(char *cmd1, int file_fd, int *pipe, char **envp)
{
	//redirect input from standard to infile
	dup2(file_fd, 0);
	dup2(pipe[1], 1);
	close(pipe[0]);
	execution(cmd1, envp);
}

void	parent_process();

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_file1;
	int		fd_file2;
	int		pipe[2];
	pid_t	id;

	open_and_check(argc, argv, &fd_file1, &fd_file2);
	if (pipe(pipe < 0))
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
		child_process(argv[2], fd_file1, pipe, envp);
	else
		parent_process(argv[3], fd_file2, pipe, envp);
}		
