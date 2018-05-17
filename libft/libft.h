/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:31:11 by rdurst            #+#    #+#             */
/*   Updated: 2018/05/17 17:47:02 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# define ISNBR(x) (x >= '0' && x <= '9')
# define ISLWR(x) (x >= 'a' && x <= 'z')
# define ISUPR(x) (x >= 'A' && x <= 'Z')
# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BBLUE "\033[1;34m"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				ft_isblanked(char c);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
size_t			ft_strlen(char const *str);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_atoi(char const *str);
char			*ft_strdup(char const *src);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
char			*ft_strcpy(char *dest, char const *src);
char			*ft_strncpy(char *dest, char const *src, size_t n);
int				ft_strucpy(char **dest, char *src, char c);
char			*ft_strncat(char *dest, char const *src, size_t n);
char			*ft_strcat(char *dest, char const *src);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
size_t			ft_strlcat(char *dst, char const *src, size_t size);
char			*ft_strchr(char const *str, int c);
char			*ft_strrchr(char const *str, int c);
char			*ft_strstr(char const *haystack, char const *needle);
void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dest, void const *src, size_t n);
void			*ft_memccpy(void *dest, void const *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(char const *s1, char const *s2, size_t n);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t n);
char			*ft_strjoin(char *s1, char *s2);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_intsize(int n);
char			*ft_itoa(int n);
void			ft_putcolor(char *color, char *str);
int				ft_trimsize(char const *str);
char			*ft_strtrim(char const *s);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
int				ft_countwords(char const *s, char c);
int				ft_wordlen(char const *s, char c);
char			**ft_strsplit(char const *s, char c);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_intendl(int n);
int				ft_nbrlen(int nb);

#endif
