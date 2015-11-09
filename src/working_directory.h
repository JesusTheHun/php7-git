#ifndef HAVE_WORKING_DIRECTORY_H

#include "php.h"
#include "php_ini.h"
#include "zend.h"
#include "ext/standard/info.h"

#include "git2.h"

const char * phpgit_working_directory_get_branch(git_repository *repo, int format);

#endif