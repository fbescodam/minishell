#ifndef CUSTOM_ERRORS_H
# define CUSTOM_ERRORS_H

# include <errno.h>

/* system errors (1 and above) */
# define PARSE_ERROR 258
# define CMDNF 127

/* minor errors (between -3 and -254) */
# define RESERVED -95

/* major errors (below -255) */
# define ERR_ENV_NOT_SET -256		// other expected environment var not set

#endif
