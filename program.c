/**************************************************************************/
/* program.c --- generate switch statements to identify string            */
/* Copyright (C) 2015 Katayama Hirofumi MZ.  All Rights Reserved.         */
/**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "make_switch.h"

/**************************************************************************/
/* the main function */

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        char *program;
        size_t i;
        program = argv[0];
        i = strcspn(program, "\\/");
        if (program[i] != 0)
        {
            program += i + 1;
        }
        printf("Usage: %s string1 string2 ...", program);
        return 0;
    }

    ms_make_identify_string_function(argc - 1, &argv[1]);

    return 0;
}

/**************************************************************************/
