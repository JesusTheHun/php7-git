#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY_H
#define HAVE_GIT_CLASS_WORKING_DIRECTORY_H

#include "php.h"
#include "php_ini.h"
#include "zend.h"
#include "ext/standard/info.h"

#include "git2.h"

enum {
  FORMAT_DEFAULT   = 0,
  FORMAT_LONG      = 1,
  FORMAT_SHORT     = 2,
  FORMAT_PORCELAIN = 3,
};

/* WorkingDirectory internal structure */

typedef struct _php_working_directory_t {
    zval        *data;
    git_repository *repo;
    zend_object  std;
} php_working_directory_t;

/* Let the world know what is a WorkingDirectory_ce */
zend_class_entry *WorkingDirectory_ce;

/* proto */
PHP_METHOD(WorkingDirectory, __construct);
PHP_METHOD(WorkingDirectory, getBranch);

/* Association of methods with the class */
extern zend_function_entry git_working_directory_methods[];

#endif