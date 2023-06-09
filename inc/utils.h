/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-la-f <jde-la-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:22:01 by adcarnec          #+#    #+#             */
/*   Updated: 2023/05/05 11:27:07 by jde-la-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *src);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *src, int start, int end);
char	*ft_trimstr(char *src);
int		ft_atoi(char *src);
int		ft_tablen(char **tab);
void	ft_freetab(char **tab);
char	**ft_tabdup(char **tab);
void	ft_printtab(char **tab);
char	**ft_split(char *src, char sep);
void	ft_putstr_fd(char *s, int fd);
int		ft_checkext(char *filename, char *ext);

#endif
