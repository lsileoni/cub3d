/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 06:54:48 by lsileoni          #+#    #+#             */
/*   Updated: 2023/08/29 06:56:26 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# define FNV_PRIME 0x100000001b3
# define FNV_OFFSET 0xcbf29ce484222325
# include <stdlib.h>
# include <unistd.h>

typedef struct s_line{
	char	*content;
	char	*beg;
	size_t	len;
}			t_line;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_dlist
{
	struct s_dlnode	*front;
	struct s_dlnode	*back;
	size_t			size;
}					t_dlist;

typedef struct s_dlnode
{
	void			*content;
	struct s_dlnode	*next;
	struct s_dlnode	*previous;
}					t_dlnode;

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}					t_vec;

typedef struct s_mmu
{
	t_list	*pointers;
	size_t	count;
}			t_mmu;

enum e_mmu_ops
{
	MMU_CREATE,
	MMU_ALLOC,
	MMU_FREE,
	MMU_DESTROY
};

typedef struct s_htelem
{
	const char	*key;
	void		*value;
}	t_htelem;

typedef struct s_hmap
{
	t_htelem	**memory;
	size_t		size;
	size_t		cap;
}	t_htable;

t_htable			*ft_htable_create(unsigned int init_size);
long long			get_message_hash(const char *message);
int					ft_htable_insert(t_htable *table,
						const char *key, void *value);
int					ft_restructure_table(t_htable *table,
						const char *key, void *value);
int					ft_probe_table(t_htable *table,
						const char *key, void *value);
int					ft_htable_insert(t_htable *table,
						const char *key, void *value);
void				*ft_htable_get(t_htable *table, const char *key);
void				ft_htable_print(t_htable *table);
int					ft_htable_remove(t_htable *table, const char *key);
void				ft_htable_destroy(t_htable *table,
						unsigned char destroy_value);
int					remove_htable_elem(t_htable *table,
						unsigned long long key_hash);
void				*mmu_op(int op, size_t data);
void				mmu_destroy(t_list *pointers, size_t flag);
void				*mmu_alloc(t_mmu *mmu, size_t size);
void				mmu_create(t_mmu *mmu);
void				mmu_free(t_mmu *mmu, void *adr);
char				*get_next_line(int fd);
char				*ft_strjoin_free(t_line *s1, char const *s2,
						const size_t s2_len);
char				*ft_strnrchr(const char *s, int c, int len);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
int					ft_i_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstadd_front(t_list **lst, t_list *_new);
void				ft_lstadd_back(t_list **lst, t_list *_new);
int					ft_lstsize(t_list *lst);
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
char				*ft_ulltoa_base(unsigned long long n, unsigned char base);
char				*ft_uitoa_base(unsigned int n, unsigned char base);
char				*ft_to_uppercase(char *str);
char				*ft_to_lowercase(char *str);
int					ft_printf(const char *args, ...);
t_dlist				*ft_dlstnew(void *content);
void				ft_dlstiter(t_dlist *lst, void (*f)(void *));
void				ft_dlstadd_back(t_dlist *lst, void *content);
t_dlnode			*ft_dlstat(t_dlist *lst, size_t n);
void				ft_dlstadd_front(t_dlist *lst, void *content);
void				ft_dlsdestroy_node(t_dlnode *node);
void				ft_dlstremove(t_dlist *lst, size_t index);
t_dlist				*ft_dlstcopy(t_dlist *src);
t_dlist				*ft_dlstsort(t_dlist *lst);

#endif
