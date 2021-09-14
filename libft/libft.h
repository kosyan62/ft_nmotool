/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgena <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 15:39:26 by mgena             #+#    #+#             */
/*   Updated: 2020/07/22 11:49:49 by mgena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define HASH_WEIGHT 12

typedef	struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_ht_item
{
	char				*key;
	char				*value;
	struct s_ht_item	*next;
}						t_ht_item;

typedef	struct
{
	unsigned int		size;
	t_ht_item			**items;
}						t_hash_table;

void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					*ft_memset (void *destination, int c, size_t n);
void					ft_bzero(void *s, size_t n);
void					*ft_memccpy(void *d, const void *s, int c, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *haystack,
						const char *needle, size_t len);
int						ft_atoi(const char *nptr);
long					ft_atol(const char *nptr);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_isdigit(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, \
							char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, \
							char const *s2, size_t n);
char					*ft_strsub(char const *s, \
							unsigned int start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
size_t					ft_strclen(const char *s, char c);
char					**ft_strsplit(char const *s, char c);
size_t					ft_wordcount(char const *s, char c);
void					ft_abortalloc(char **res, size_t k);
int						ft_countdigits(int n);
char					*ft_itoa(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstaddend(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int						ft_printf(const char *format, ...);
int						ft_fdprintf(int fd, const char *format, ...);
char					*ft_realloc_double(char *str);
_Bool					ft_isspace(int ch);
int						get_next_line(const int fd, char **line);
long					ft_pow(int a, int b);
void					malloc_error();
t_ht_item				*new_ht_item(char *key, char *value);
t_hash_table			*new_hash_table(unsigned int size);
void					ht_del_item(t_ht_item *item);
void					del_hash_table(t_hash_table *table);
unsigned int			hash_funct(char *string, int a, int count);
void					ht_insert(t_hash_table *table, char *key, char *value);
char					*ht_search(t_hash_table *table, char *key);
void					ht_del_elem(t_hash_table *table, char *key);
void					ht_print_whole(t_hash_table *table);
void					ft_bubble_sort(void **array, size_t len, int(*func)(void*, void*));
uint32_t				ft_swap_uint32(uint32_t n);
void ft_qsort(void* v, int size, int left, int right,
			  int (*comp)(void*, void*));
#endif
