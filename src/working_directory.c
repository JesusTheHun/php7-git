#ifndef HAVE_WORKING_DIRECTORY
#define HAVE_WORKING_DIRECTORY

char * void phpgit_working_directory_get_branch(git_repository *repo, int format) {
    int error = 0;
    const char *branch = NULL;
    git_reference *head = NULL;

    error = git_repository_head(&head, repo);

    if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
        zend_throw_exception("Exception", "Branch not found", 404);
    else if (!error) {
        branch = git_reference_shorthand(head);
    } else


    if (format == FORMAT_LONG)
        printf("# On branch %s\n", branch ? branch : "Not currently on any branch.");
        zend_throw_exception("Exception", "Not currently on any branch", 0);
    else
        if (branch) {
             RETURN_NEW_STR(branch);
        } else {
            zend_throw_exception("Exception", "HEAD (no branch)", 1);
        }

    git_reference_free(head);
}