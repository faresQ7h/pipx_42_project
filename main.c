/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fares-_-q7h <fares-_-q7h@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 22:04:02 by fares-_-q7h       #+#    #+#             */
/*   Updated: 2025/09/12 02:09:03 by fares-_-q7h      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipx.h"

char *cmnd_path(char **envp)
{
    int i;
    char *path;

    i = 0;
    while(envp[i])
    {
        
    }
}

int main(int argc, char **argv, char **envp)
{
    int fd;
    pid_t pid;
    char *path;
    int status;
    int ext_code;
    int pip[2];

    if (argc != 5)
        return(ft_printf("Error!\nUsage: ./pipex file1 cmd1 cmd2 file2\n"), 1);
    if(pipe(pip) < 0)
        return(perror("pipe"), errno);
    pid = fork();
    if(pid != 0) // parent process for cmd2
    {
        fd = open(argv[4], O_CREAT|O_WRONLY|O_TRUNC, 0644);
        if (fd < 0)
            return(perror(argv[4]), errno);
        close(pip[1]);
        if (dup2(pip[0], STDIN_FILENO) != STDIN_FILENO || dup2(fd, STDOUT_FILENO) != STDOUT_FILENO)
            return(perror("Error"), errno);    
        if(WIFEXITED(status)) //check if the chiled process exited normally through exit or return in main
        {
            ext_code = WEXITSTATUS(status); 
            if(ext_code != 0)
                ft_printf("Error!\n cmd1: Error_code: %d", ext_code);
        }
        else if (WIFSIGNALED(status))
            ft_printf("Error!\ncmd1: Error_code: %d", 127 + WTERMSIG(status));
        path = cmnd_path(envp);
        close(pip[0]);
    }
    else // chiled process for cmd1
    {
        fd = open(argv[1], O_RDONLY);
        if(fd < 0)
            return(close(pip[0]), close(pip[1]), perror(argv[1]), errno);
        close(pip[0]);
        if (dup2(fd, STDIN_FILENO) != STDIN_FILENO || dup2(pip[1], STDOUT_FILENO) != STDOUT_FILENO)
            return(perror("Error"), errno);
        path = cmnd_path(envp);
        close(pip[1]);
    }
    close(fd);
    return(0);
}