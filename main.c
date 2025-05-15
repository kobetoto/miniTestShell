/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:33:13 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/15 14:57:21 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/*
██      ██ ██████  ███████ ████████ 
██      ██ ██   ██ ██         ██    
██      ██ ██████  █████      ██    
██      ██ ██   ██ ██         ██    
███████ ██ ██████  ██         ██    
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 1);
	exit(0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] && s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strchr(const char *s, int n)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)n)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)n == 0)
		return ((char *)s);
	return (0);
}
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	size_str;

	size_str = ft_strlen(src);
	if (size == 0)
		return (size_str);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (size_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	l;

	l = ft_strlen(s);
	if (start > l)
		start = l;
	if (len > l - start)
		len = l - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i] && (s1[i] && s2[i]) && i < n))
		i++;
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}

char	*ft_strdup(const char *src)
{
	char	*s;
	int		l;
	int		i;

	if (!src)
		return (NULL);
	l = ft_strlen(src);
	s = (char *)malloc((l + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (i < l)
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
/*
███████ ██   ██ ███████ ██      ██      
██      ██   ██ ██      ██      ██      
███████ ███████ █████   ██      ██      
     ██ ██   ██ ██      ██      ██      
███████ ██   ██ ███████ ███████ ███████ 
*/



char *ft_old_pwd(char **envp)
{
    int     i;
    int     j;
    char    *old_pwd;
    char    *o_p_path;
    
    i = 0;
    j = 0;
    while (envp[i])
        i++;
    while(j < i)
    {
        if(ft_strncmp(envp[j], "OLDPWD", 6) == 0)
            old_pwd = envp[j];
        j++;
    }
    o_p_path = ft_strchr(old_pwd, '/');
    return (o_p_path);
}

char *ft_pwd(char **envp)
{
    int     i;
    int     j;
    char    *pwd;
    
    i = 0;
    j = 0;
    while (envp[i])
        i++;
    while(j < i)
    {
        if(ft_strncmp(envp[j], "PWD", 3) == 0)
            pwd = envp[j];
        j++;
    }
    printf("==%s==\n", pwd);
    return (pwd);
}

int ft_cd_back(char **envp)
{
    char    *old_pwd;
    int     chdir_r;
    
    old_pwd = ft_old_pwd(envp);
    chdir_r = 0;
    chdir_r = chdir(old_pwd);
    if (chdir_r != 0)
    {
        printf("==ERR== chdir() err\n");
        return (1);
    }
    return (0);
}

char **ft_envp_copy(char **envp)
{
    char **envp_cpy;
    int var_count;
    int i;

    i = 0;
    var_count = 0;
    while(envp[var_count])
        var_count++;
    envp_cpy = malloc(sizeof(char *) * (var_count +1));
    if (envp_cpy == NULL)
        ft_error("==ERR== malloc envp_cpy");
    while(envp[i])
    {
        envp_cpy[i] = ft_strdup(envp[i]);
        if(envp_cpy[i] == NULL)
            ft_error("==ERR== envp_cpy dup");
        i++;
    }
    /*
    En cas d’échec d’allocation d’un élément, 
    tu pourrais libérer tous les éléments déjà alloués 
    (envp_cpy[0] à envp_cpy[i - 1]) 
    pour éviter les memory leaks (fuite mémoire).
    */
    envp_cpy[i] = NULL;
    return (envp_cpy);
}

/*
███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 
*/

int main(int ac, char **av, char **envp)
{
    int check_chdir;
    char **envp_copy;
    char pwd[1000];
    (void) ac;
    (void) av;

    check_chdir = 0;
    envp_copy = ft_envp_copy(envp);
    while (1)
    {
    //prompt//
    char *line = readline("minishell$ ");
    //exit//
    if (!line || line[0] == 'e')
        exit(0); 
    //history//
    if (*line)
        add_history(line);
    //check cmd//
    //cd
    if (ft_strcmp(line, "cd ..") == 0)
    {
        check_chdir = ft_cd_back(envp);
        printf("==%i==\n",check_chdir);
    }
    //pwd
    if (ft_strcmp(line, "pwd") == 0)
        printf("%s\n", getcwd(pwd, 100));
    //free//
    free(line);
    }
    return (0);
}

