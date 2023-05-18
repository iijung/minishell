/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:41:55 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/19 00:54:13 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H
# include "environ.h"
# include "lexer.h"

extern t_list		*get_wildcard(char *str);
extern int			get_heredoc(t_env **table, char *word);
extern t_lex_lst	*combine_string(t_env **table, t_lex_lst *curr, char **dst);

#endif
