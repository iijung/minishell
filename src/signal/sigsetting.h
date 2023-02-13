/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigsetting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 21:42:58 by jaemjeon          #+#    #+#             */
/*   Updated: 2023/02/13 22:14:17 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGSETTING_H
# define SIGSETTING_H

void	signal_handler(int signo);
void	signal_event(void);
void	setting_signal(int option);

#endif