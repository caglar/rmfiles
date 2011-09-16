/*
 * =====================================================================================
 *
 *       Filename:  rm_files.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/16/2011 11:52:35 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Caglar GULCEHRE, 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

char *
c_trim(char *str)
{
    size_t len = 0;
    char *frontp = str - 1;
    char *endp = NULL;

    if (str == NULL)
        return NULL;

    if (str[0] == '\0')
        return str;

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address
     * the first non-whitespace characters from
     * each end.
     */
    while (isspace(*(++frontp)))
        ;
    while (isspace(*(--endp)) && endp != frontp)
        ;

    if (str + len - 1 != endp)
        *(endp + 1) = '\0';
    else if (frontp != str && endp == frontp)
        *str = '\0';

    /* Shift the string so that it starts at str so
     * that if it's dynamically allocated, we can
     * still free it on the returned pointer.  Note
     * the reuse of endp to mean the front of the
     * string buffer now.
     */
    endp = str;
    if (frontp != str) {
        while (*frontp)
            *endp++ = *frontp++;
        *endp = '\0';
    }

    return str;
}

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *ent;
    int count;
    char *directory = "";
    char *suffix = "";
    if (argc > 2)
    {
        directory = c_trim(argv[1]);
        suffix = c_trim(argv[2]);
    }
    else
    {
        printf("The command had no other arguments.\n");
    }

    dir = opendir (directory);
    if (dir != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, ".."))) {
                if ((strcasestr(ent->d_name, suffix) != NULL)) {

                    //Efficient concat strings:
                    size_t len1 = strlen(directory);
                    size_t len2 = strlen(ent->d_name);

                    char * file = malloc(len1 + len2 +2);
                    strcpy(file, directory);
                    strcat(file, ent->d_name);
        //            printf("File is being removed %s\n", file);
                    if (remove(file)  == -1) {
                        syslog(LOG_PERROR, "Couldn't remove the file %s.\n", ent->d_name);
                    }
                }
            }
        }
        closedir (dir);
    } else {
        perror ("Couldn't open the directory");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
