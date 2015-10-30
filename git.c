/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_git.h"



static int le_git;







PHP_MINIT_FUNCTION(git)
{
	return SUCCESS;
}


PHP_MSHUTDOWN_FUNCTION(git)
{
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

