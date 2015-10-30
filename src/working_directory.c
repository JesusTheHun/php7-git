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

void phpgit_working_directory_get_status(zval* status) {
    const git_status_entry *s;
    int header = 0,
        changes_in_index = 0,
        changed_in_workdir = 0,
        rm_in_workdir = 0
    ;
    const char *old_path, *new_path;

    uint_32 i, maxi = git_status_list_entrycount(status);

    for (i = 0; i < maxi; ++i) {

        char *istatus = NULL;
        zval *entry_status;

        array_init(entry_status);

        s = git_status_byindex(status, i);

        if (s->status == GIT_STATUS_CURRENT) {
            continue;
        }

        if (s->status & GIT_STATUS_WT_DELETED)
            rm_in_workdir = 1;
        if (s->status & GIT_STATUS_INDEX_NEW)
            istatus = "new file: ";
        if (s->status & GIT_STATUS_INDEX_MODIFIED)
            istatus = "modified: ";
        if (s->status & GIT_STATUS_INDEX_DELETED)
            istatus = "deleted:  ";
        if (s->status & GIT_STATUS_INDEX_RENAMED)
            istatus = "renamed:  ";
        if (s->status & GIT_STATUS_INDEX_TYPECHANGE)
            istatus = "typechange:";

        if (istatus == NULL) {
            continue;
        }

        zend_hash_update(Z_ARRVAL_P(entry_status), "staged", 0);
        zend_hash_update(Z_ARRVAL_P(entry_status), "status", s->status);

        if (!header) {
            printf("# Changes to be committed:\n");
            printf("#   (use \"git reset HEAD <file>...\" to unstage)\n");
            printf("#\n");
            header = 1;
        }

        old_path = s->head_to_index->old_file.path;
        new_path = s->head_to_index->new_file.path;

        zend_hash_update(Z_ARRVAL_P(entry_status), "oldPath", s->head_to_index->old_file.path);
        zend_hash_update(Z_ARRVAL_P(entry_status), "newPath", s->head_to_index->new_file.path);
    }

    if (header) {
        changes_in_index = 1;
    }

  header = 0;

      for (i = 0; i < maxi; ++i) {
          char *wstatus = NULL;

          s = git_status_byindex(status, i);

            /* With GIT_STATUS_OPT_INCLUDE_UNMODIFIED (not used in this example) index_to_workdir may not be NULL even if there are no differences,
               in which case it will be a GIT_DELTA_UNMODIFIED. */

          if (s->status == GIT_STATUS_CURRENT || s->index_to_workdir == NULL)
            continue;

            /*
            Print out the output since we know the file has some changes
            */

          if (s->status & GIT_STATUS_WT_MODIFIED)
            wstatus = "modified: ";
          if (s->status & GIT_STATUS_WT_DELETED)
            wstatus = "deleted:  ";
          if (s->status & GIT_STATUS_WT_RENAMED)
            wstatus = "renamed:  ";
          if (s->status & GIT_STATUS_WT_TYPECHANGE)
            wstatus = "typechange:";

          if (wstatus == NULL)
            continue;

          if (!header) {
            printf("# Changes not staged for commit:\n");
            printf("#   (use \"git add%s <file>...\" to update what will be committed)\n", rm_in_workdir ? "/rm" : "");
            printf("#   (use \"git checkout -- <file>...\" to discard changes in working directory)\n");
            printf("#\n");
            header = 1;
          }

          old_path = s->index_to_workdir->old_file.path;
          new_path = s->index_to_workdir->new_file.path;

          if (old_path && new_path && strcmp(old_path, new_path))
            printf("#\t%s  %s -> %s\n", wstatus, old_path, new_path);
          else
            printf("#\t%s  %s\n", wstatus, old_path ? old_path : new_path);
        }

        if (header) {
          changed_in_workdir = 1;
          printf("#\n");
        }

        /* Print untracked files */

        header = 0;

        for (i = 0; i < maxi; ++i) {
          s = git_status_byindex(status, i);

          if (s->status == GIT_STATUS_WT_NEW) {

            if (!header) {
              printf("# Untracked files:\n");
              printf("#   (use \"git add <file>...\" to include in what will be committed)\n");
              printf("#\n");
              header = 1;
            }

            printf("#\t%s\n", s->index_to_workdir->old_file.path);
          }
        }

        header = 0;

      /* Print ignored files */


        for (i = 0; i < maxi; ++i) {
          s = git_status_byindex(status, i);

          if (s->status == GIT_STATUS_IGNORED) {

            if (!header) {
              printf("# Ignored files:\n");
              printf("#   (use \"git add -f <file>...\" to include in what will be committed)\n");
              printf("#\n");
              header = 1;
            }

            printf("#\t%s\n", s->index_to_workdir->old_file.path);
          }
        }

        if (!changes_in_index && changed_in_workdir)
          printf("no changes added to commit (use \"git add\" and/or \"git commit -a\")\n");
    }
}