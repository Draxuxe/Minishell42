/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:01:39 by rblondia          #+#    #+#             */
/*   Updated: 2022/05/09 17:25:25 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/**
 * Libraries
 */
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/**
 * Structures
 */
typedef struct s_word
{
	unsigned int	start;
	size_t			len;
}				t_word;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/**
 * Main functions
 */
int		ft_strchr_neg(const char *s, int c);
int		ft_strcchr(const char *s, char *sep);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_calloc(size_t nelem, size_t elsize);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_tolower(int a);
int		ft_toupper(char a);
char	*ft_strdup(const char *s);
int		ft_atoi(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strcmp_sensitive(const char *a, const char *b);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *a, const char *b);
char	*ft_strjoin_properly(char *s1, char *s2);
int		ft_strcomp_valid(char *s1, char *s2);
int		ft_strchr_bis(const char *s, int c);

/**
 * Additional functions
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char *s1, char const *set);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * Bonus functions
 */
t_list	*ft_lstnew(void *content);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstadd_back(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);

#endif