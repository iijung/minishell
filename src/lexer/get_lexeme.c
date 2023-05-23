/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lexeme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 02:48:29 by minjungk          #+#    #+#             */
/*   Updated: 2023/05/21 00:57:01 by minjungk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "util.h"

void	lexeme_debug(void *param)
{
	const struct s_lexeme	*c = param;
	const char				*typename[] = {
	[LEXEME_STRING] = "STRING",
	[LEXEME_EOF] = "EOF",
	[LEXEME_IFS] = "IFS",
	[LEXEME_OR] = "OR",
	[LEXEME_AND] = "AND",
	[LEXEME_HEREDOC] = "HEREDOC",
	[LEXEME_ADDFILE] = "ADDFILE",
	[LEXEME_OUTFILE] = "OUTFILE",
	[LEXEME_INFILE] = "INFILE",
	[LEXEME_PIPE] = "PIPE",
	[LEXEME_QUOTE] = "QUOTE",
	[LEXEME_DQUOTE] = "DQUOTE",
	[LEXEME_WILDCARD] = "WILDCARD",
	[LEXEME_ENVIRONMENT] = "ENVIRONMENT",
	[LEXEME_PARENTHESIS_OPEN] = "PARENTHESIS_OPEN",
	[LEXEME_PARENTHESIS_CLOSE] = "PARENTHESIS_CLOSE"};

	if (c == NULL)
		return ;
	printf("lexeme [%x: %12s] len[%lu] data[%.*s]\n",
		c->type, typename[c->type], c->len, (int)c->len, c->data);
}

enum e_lexeme	lexeme_type(t_lex_lst *curr)
{
	if (curr == NULL || curr->content == NULL)
		return (LEXEME_EOF);
	return (((struct s_lexeme *)(curr->content))->type);
}

size_t	lexeme_len(t_lex_lst *curr)
{
	if (curr == NULL || curr->content == NULL)
		return (0);
	return (((struct s_lexeme *)(curr->content))->len);
}

const char	*lexeme_data(t_lex_lst *curr)
{
	if (curr == NULL || curr->content == NULL)
		return (NULL);
	return (((struct s_lexeme *)(curr->content))->data);
}

char	*lexeme_str(t_lex_lst *curr)
{
	struct s_lexeme	*content;

	if (curr == NULL || curr->content == NULL)
		return (NULL);
	content = curr->content;
	return (ft_strndup(content->data, content->len));
}
