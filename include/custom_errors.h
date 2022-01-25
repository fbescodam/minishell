/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   custom_errors.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/06 18:00:05 by jgalloni      #+#    #+#                 */
/*   Updated: 2022/01/25 18:34:52 by jgalloni      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUSTOM_ERRORS_H
# define CUSTOM_ERRORS_H

/* system errors (1 and above) */

/* exit codes -1 and -2 are used to exit minishell normally */	// TODO: change that to 0 and -1?
/* minor errors (between -3 and -254) */

/* major errors (below -255) */
# define ERR_PATH_MISSING -255		// PATH system env variable not set
# define ERR_ENV_NOT_SET -256		// other expected system env var not set

/* TODO change these error codes */
# define PARSE_ERROR 258
# define CMDNF 127
# define RESERVED 95

#include <errno.h>

#endif
