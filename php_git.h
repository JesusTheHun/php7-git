#ifndef PHP_GIT_H
#define PHP_GIT_H
#define PHP_GIT_EXTNAME "git"
#define PHP_GIT_VERSION "0.1alpha"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "zend.h"
#include "ext/standard/info.h"

#include "git2.h"

/* Some common stuff */

void phpgit_init(void);
void phpgit_throw_exception_on_libgit_error(int error);
/* Association of methods with the class */



/* Let's include class def */

#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY_H
#include <classes/working_directory.h>
#endif


extern zend_module_entry git_module_entry;
#define phpext_git_ptr &git_module_entry

#endif