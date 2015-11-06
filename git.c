#include "php_git.h"

void phpgit_init(void) {

    zend_class_entry ce;
    zend_object_handlers *zh;

    zend_object_handlers php_gitwd_handlers;

    INIT_CLASS_ENTRY(ce, "WorkingDirectory", git_working_directory_methods);
    WorkingDirectory_ce = zend_register_internal_class(&ce);

    zh = zend_get_std_object_handlers();

    memcpy(&php_gitwd_handlers, zh, sizeof(zend_object_handlers));
}

void phpgit_throw_exception_on_libgit_error(int error) {

    const git_error *lg2err;

    if (!error) {
        return;
    }

    if ((lg2err = giterr_last()) != NULL && lg2err->message != NULL) {
        zend_throw_exception(lg2err->message, lg2err->klass);
        return;
    }

    zend_error(E_ERROR, "libgit2 unknown error, this should never happen");
}

PHP_MINIT_FUNCTION(git)
{
    git_libgit2_init(); /* libgit2 initialization */
    phpgit_init();
    return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(git)
{
    git_libgit2_shutdown(); /* libgit2 shutdown */
    return SUCCESS;
}



PHP_RINIT_FUNCTION(git)
{
#if defined(COMPILE_DL_GIT) && defined(ZTS)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif
    return SUCCESS;
}



PHP_RSHUTDOWN_FUNCTION(git)
{
    return SUCCESS;
}


PHP_MINFO_FUNCTION(git)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "git support", "enabled");
    php_info_print_table_end();

}


const zend_function_entry git_functions[] = {
    PHP_FE_END
};


zend_module_entry git_module_entry = {
    STANDARD_MODULE_HEADER,
    "git",
    git_functions,
    PHP_MINIT(git),
    PHP_MSHUTDOWN(git),
    PHP_RINIT(git),
    PHP_RSHUTDOWN(git),
    PHP_MINFO(git),
    PHP_GIT_VERSION,
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_GIT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(git)
#endif

