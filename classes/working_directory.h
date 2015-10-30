#ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY_H
#define HAVE_GIT_CLASS_WORKING_DIRECTORY_H

PHP_METHOD(WorkingDirectory, getStatus);

ZEND_BEGIN_ARG_INFO(WorkingDirectory_getStatus, 0)



extern zend_function_entry git_working_directory_methods[];

#else
#	ifndef HAVE_GIT_CLASS_WORKING_DIRECTORY
#	define HAVE_GIT_CLASS_WORKING_DIRECTORY

zend_function_entry git_working_directory_methods[] = {
    PHP_ME(WorkingDirectory, getStatus, Thread_start, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

/*****************/
/* CLASS METHODS */
/*****************/

/* Print git status (testing purpose) */

PHP_METHOD(WorkingDirectory, getStatus)
{
    ZVAL_ARR(return_value, phpgit_working_directory_get_status());
}

#	endif
#endif