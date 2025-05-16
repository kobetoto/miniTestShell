/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:33:13 by thodavid          #+#    #+#             */
/*   Updated: 2025/05/16 15:02:31 by thodavid         ###   ########.fr       */
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

char	**ft_free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

int	ft_count_word(char const *str, char ch)
{
	size_t	i;
	size_t	trigger;

	if (!str)
		return (0);
	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != ch && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == ch)
			trigger = 0;
		str++;
	}
	return (i);
}

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    while (*s)
    {
        ft_putchar_fd(*s, fd);
        s++;
    }
}

void ft_putendl_fd(char *s, int fd)
{
    ft_putstr_fd(s, fd);
    ft_putchar_fd('\n', fd);
}

void ft_error(char *str)
{
    ft_putendl_fd(str, 1);
    exit(0);
}

size_t ft_strlen(const char *str)
{
    int i;

    i = 0;

    while (str[i])
        i++;
    return (i);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while ((s1[i] == s2[i]) && (s1[i] && s2[i]))
        i++;
    return (s1[i] - s2[i]);
}

char *ft_strchr(const char *s, int n)
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
size_t ft_strlcpy(char *dest, const char *src, size_t size)
{
    size_t i;
    size_t size_str;

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

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    char *str;
    unsigned int l;

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

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

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

char *ft_strdup(const char *src)
{
    char *s;
    int l;
    int i;

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

/**
 * @brief Recherche la première occurrence d'une sous-chaîne dans
 * une chaîneprincipale, avec une limite.
 *
 * La fonction `ft_strnstr` recherche la première occurrence de
 * la sous-chaîne `to_find` dans la chaîne principale `str`, en ne
 * parcourant que les `size` premiers caractères de `str`. Si `to_find` est
 * une chaîne vide, la fonction retourne immédiatement `str`. Si `to_find`
 * est trouvé dans `str` dans la limite spécifiée, la fonction retourne
 * un pointeur vers le début de la première occurrence.
 * Si `to_find` n'est pas trouvé ou si `size` est nul, la fonction retourne
 * `NULL`.
 *
 * @param str La chaîne principale dans laquelle rechercher.
 * @param to_find La sous-chaîne à rechercher dans `str`.
 * @param size Le nombre de caractères dans `str` à parcourir.
 *
 * @return Un pointeur vers la première occurrence de `to_find` dans `str`,
 *  ou `NULL` si la sous-chaîne n'est pas trouvée.
 *
 * @note Cette fonction est utile pour effectuer des recherches dans des chaînes
 *  en limitant la recherche à un certain nombre de caractères, ce qui peut être
 * 	utile pour les recherches dans des portions spécifiques d'une chaîne ou pour
 * 	optimiser la recherche dans de grandes chaînes.
 */
char *ft_strnstr(const char *str, const char *to_find, size_t size)
{
    size_t l_to_find;
    size_t i;
    char *s1;

    l_to_find = ft_strlen(to_find);
    s1 = (char *)str;
    i = 0;
    if (to_find[0] == '\0')
        return (s1);
    if (size == 0 || s1[0] == '\0')
    {
        return (NULL);
    }
    while (i < size)
    {
        if (ft_strncmp(s1, (char *)to_find, l_to_find) == 0)
        {
            if (i + l_to_find > size)
                return (NULL);
            return (s1);
        }
        s1++;
        i++;
    }
    return (0);
}

static char **ft_to_write(char const *src, char c, char **split, size_t l_word)
{
    size_t i;
    size_t j;

    i = -1;
    j = 0;
    while (src[++i])
    {
        if (src[i] != c)
            l_word++;
        else if (src[i] == c && l_word > 0)
        {
            split[j] = ft_substr(src, (i - l_word), l_word);
            if (!split[j++])
                return (ft_free_split(split), NULL);
            l_word = 0;
        }
    }
    if (l_word > 0)
    {
        split[j++] = ft_substr(src, (i - l_word), l_word);
        if (!split[j - 1])
            return (ft_free_split(split), NULL);
    }
    return (split[j] = NULL, split);
}
/**
 * @brief Divise une chaîne de caractères en sous-chaînes en fonction d'un
 * 	séparateur.
 *
 * La fonction `ft_split` prend une chaîne de caractères `s` et un séparateur
 * `c`, et divise la chaîne en sous-chaînes. Elle retourne un tableau de chaînes,
 * où chaque élément est une sous-chaîne de `s` séparée par le caractère `c`.
 * La fonction alloue dynamiquement de la mémoire pour chaque sous-chaîne et le
 * tableau retourné. Si une erreur d'allocation se produit, la fonction libère
 * toute la mémoire précédemment allouée et retourne `NULL`.
 *
 * @param s La chaîne de caractères à diviser.
 * @param c Le caractère séparateur utilisé pour diviser la chaîne.
 *
 * @return Un tableau de sous-chaînes. Si l'allocation échoue, retourne `NULL`.
 *
 * @note La fonction alloue dynamiquement la mémoire pour chaque sous-chaîne
 * 	et pour le tableau.Il est donc important de libérer cette mémoire une fois
 * 	qu'elle n'est plus utilisée.
 */
char **ft_split(char const *src, char c)
{
    char **split;

    split = (char **)malloc((ft_count_word(src, c) + 1) * sizeof(char *));
    if (!split)
        return (NULL);
    split = ft_to_write(src, c, split, 0);
    return (split);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;
	size_t	j;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	i = 0;
	j = dest_size;
	if (size <= dest_size || size == 0)
		return (src_size + size);
	while (src[i] && i < size - dest_size - 1)
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest_size + src_size);
}

char	*ft_strjoin(char *s1, char *s2, int f1, int f2)
{
	int		len_s1;
	int		len_s2;
	char	*new_s;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_s = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, len_s1 + 1);
	ft_strlcat(new_s, s2, len_s1 + len_s2 + 1);
	if (f1 && s1)
		free(s1);
	if (f2 && s2)
		free(s2);
	return (new_s);
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
    int i;
    int j;
    char *old_pwd;
    char *o_p_path;

    i = 0;
    j = 0;
    while (envp[i])
        i++;
    while (j < i)
    {
        if (ft_strncmp(envp[j], "OLDPWD", 6) == 0)
            old_pwd = envp[j];
        j++;
    }
    o_p_path = ft_strchr(old_pwd, '/');
    return (o_p_path);
}

char *ft_search_pwd(char **envp_c)
{
    int i;
    int j;
    char *pwd;

    i = 0;
    j = 0;
    while (envp_c[i])
    { 
        if (ft_strncmp(envp_c[i], "PWD", 3) == 0)
            pwd =  ft_strchr(envp_c[i], '/');
        i++;
    }
    return (pwd);
}

void ft_export(char ***envp_c, char *key, char *value)
{
    (void) value;
    int i;
    int key_len;
    char ** env;
    char *new_line;
    char *full_line;

    i = 0;
    key_len = ft_strlen(key);
    env = *envp_c;
    while(env[i])
    {
        if(ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
        {
            //je remplace value de la ligne dans le tablaeu ENVP_C
            free(env[i]);
            new_line = ft_strjoin(key, "=", 0, 0);
            full_line = ft_strjoin(new_line, value, 1, 0);
            env[i] = full_line;
            return ;
        }
        i++;
    }
}

int ft_cd(char ***envp_c, char *line)
{
    char **cmd;
    char  *pwd;
    char  *dst;
    char  *path;
    int chdir_r;


    chdir_r = 0;
    cmd = ft_split(line, ' ');
    if (cmd[2])
        {
            printf("==ERR== cd too many arg");
            return (0);
        }
    pwd = ft_search_pwd(*envp_c);
    dst = ft_strjoin(pwd, "/", 0, 0);
    path = ft_strjoin(dst, cmd[1], 0, 0);
    ft_export(envp_c, "PWD", path);
    return (0);
}

int ft_cd_back(char **envp)
{
    char *old_pwd;
    int chdir_r;

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
    int j;

    i = 0;
    j = 0;
    var_count = 0;
    while (envp[var_count])
        var_count++;
    envp_cpy = malloc(sizeof(char *) * (var_count + 1));
    if (envp_cpy == NULL)
        ft_error("==ERR== malloc envp_cpy");
    while (envp[i])
    {
        envp_cpy[i] = ft_strdup(envp[i]);
        /*
        En cas d’échec d’allocation d’un élément,
        tu pourrais libérer tous les éléments déjà alloués
        (envp_cpy[0] à envp_cpy[i - 1])
        pour éviter les memory leaks (fuite mémoire).
        POSSIBLE DE LE METTRE CETTE FUNCTION DANS UNE AUTRE FONCTION
        */
        if (envp_cpy[i] == NULL)
        {
            while (j < i)
            {
                free(envp_cpy[j]);
                j++;
            }
            free(envp_cpy);
            ft_error("==ERR== envp_cpy dup");
        }
        i++;
    }
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
    int i;
    char **envp_copy;
    char pwd[1000];
    (void)ac;
    (void)av;

    i = 0;
    // copy de env
    envp_copy = ft_envp_copy(envp);

    while (1)
    {
        // prompt//
        char *line = readline("minishell$ ");
        // exit//
        if (!line || line[0] == '!')
            exit(0);
        // history//
        if (*line)
            add_history(line);
            
        // cmd//
        // cd
        if (ft_strnstr(line, "cd ", 3) != NULL)
            ft_cd(&envp_copy, line);
        // pwd
        if (ft_strcmp(line, "pwd") == 0)
            printf("%s\n", ft_search_pwd(envp_copy));
        //print envcp
        if (ft_strcmp(line, "env") == 0)
        {
            i = 0;
            while (envp_copy[i])
            {
                printf("%s\n", envp_copy[i]);
                i++;
            }
            
        }
        // free//
        free(line);
    }
    return (0);
}

