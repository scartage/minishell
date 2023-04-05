/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoares- <fsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:16:50 by fsoares-          #+#    #+#             */
/*   Updated: 2023/04/05 16:54:34 by fsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <sys/types.h>
# include <stdbool.h>

# define BRED  "\x1B[1;31m"
# define RED   "\x1B[0;31m"
# define BGRN  "\x1B[1;32m"
# define GRN   "\x1B[0;32m"
# define YEL   "\x1B[0;33m"
# define BLU   "\x1B[0;34m"
# define BMAG  "\x1B[1;35m"
# define MAG   "\x1B[0;35m"
# define CYN   "\x1B[0;36m"
# define BCYN  "\x1B[1;36m"
# define BWHT  "\x1B[1;37m"
# define NC    "\x1B[0m"

typedef struct s_string {
	char	*buffer;
	size_t	size;
	size_t	current;
}	t_string;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef unsigned char	t_byte;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

int			ft_atoi(const char *str);
long		ft_atol(const char *str);
char		*ft_itoa(int n);

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		ft_strrev(char *str);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);

char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

void		*ft_calloc(size_t count, size_t size);

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **list, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **list, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int			ft_printf(const char *format, ...);
/**
 * @brief Equal to ft_printf, but adds a newline at the end
 */
int			ft_printfln(const char *format, ...);
char		*get_next_line(int fd);

// Extra functions

char		*to_lower_str(char *str);
void		terminate_with_error(char *message);
void		*protected_calloc(size_t count, size_t size);
void		*protected_malloc(size_t size);
double		ft_atof(const char *str);

/**
 * @brief Unquotes a word.
 * Removes the surrounding quotes and also if there are any escaped quotes
 * in the string, also unescapes them.
 *
 * For example:
 *     unquote('"test with \" quote"'): 'test with " quote'
 *
 * @param word The word to be unquoted
 * @return char* A new string, without the quotes.
 */
char		*unquote(char *word);

void		ft_free_split(char **split);

char		*free_builder(t_string *builder);
t_string	*new_builder(void);

/**
 * @brief Appends new to the current buffer. If there is not enough space it
 * will double the buffer size and copy the string
 *
 * @param string	The autoexpansive string that will handle a random value size
 * @param new		The new chars to add to the buffer
 * @param new_size	The number of chars to add to the string
 *
 * @return int		A flag that signals if everything went ok. Returns -1 if it
 * 					failed a malloc, 1 otherwise.
 */
int			append_string(t_string *string, char *str);
int			append_char(t_string *string, char new);
void		reset_builder(t_string *string);

#endif
