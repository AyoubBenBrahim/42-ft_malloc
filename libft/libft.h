/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayb***** <ayb*****@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:27:37 by ayb*****          #+#    #+#             */
/*   Updated: 2020/01/16 15:36:26 by ayb*****         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H
# define BUFF_SIZE 2

# include "ft_printf/inc/ft_printf.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

#include <stdbool.h>



int                 get_next_line(const int fd, char **line);
size_t              ft_strlen(const char *s);
char                *ft_strcpy(char *dst, const char *src);
char                *ft_strdup(const char *s1);
char                *ft_strstr(const char *haystack, const char *needle);
int	                ft_atoi(const char *str);
int	                ft_isspace(int c);
int	                ft_strncmp(const char *s1, const char *s2, size_t n);
char                *ft_strchr(const char *s, int c);
char                *ft_strrchr(const char *s, int c);
void                *ft_memset(void *b, int c, size_t len);
int	                ft_memcmp(const void *s1, const void *s2, size_t n);
void                ft_bzero(void *s, size_t n);
void                *ft_memalloc(size_t size);
void                ft_memdel(void **ap);
char                *ft_strnew(size_t size);
int                 ft_strdel(char **as);
char                *ft_strsub(char const *s, unsigned int start, size_t len);
int                 ft_putchar(char c);
void                ft_putnbr(int n);
int	                ft_isdigit(int c);
int                 ft_putstr(char const *s);
char                *ft_strjoin(char const *s1, char const *s2);
char                *ft_strcat(char *s1, const char *s2);
int	                is_number(char *str);
int                 ft_strcmp(const char *s1, const char *s2);
long long int       ft_atoll(const char *str);
void                *ft_memcpy(void *dst, const void *src, size_t n);
int                 ft_islower(int c);
int                 ft_isupper(int c);
char                *ft_ltoa(long long n);
void                ft_putnchar(char c, long n);
int                 ft_contains(const char *set, char c);
char                *ft_strndup(const char *s, size_t times);
char                *ft_utoa(unsigned long long n);
int                 ft_indexof(char *s, char c);
long                ft_abs(long nb);
char                *ft_strjoin_free(char *s1, char *s2);
void                ft_strupper(char *str);
int                 ft_toupper(int c);
int                 ft_tolower(int c);
bool                is_in_range(int value, int lower_bound, int upper_bound);
char*               ft_strpbrk(const char* str, const char* chars);


#endif
