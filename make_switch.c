#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "make_switch.h"

void ms_do_indent(int n)
{
    int i, j;
    if (MS_TAB_WIDTH < 0)
    {
        for (i = 0; i < n; ++i)
        {
            putchar('\t');
        }
    }
    else
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < MS_TAB_WIDTH; ++j)
            {
                putchar(' ');
            }
        }
    }
}

void ms_make_switch(MS_MAKE_SWITCH *pms, int depth, int ident_level)
{
    int i;
    for (i = 0; i < pms->count; ++i)
    {
        if (pms->checks[i] || memcmp(pms->entries[i], pms->str, depth))
        {
            continue;
        }
        ms_do_indent(ident_level);
        if (pms->entries[i][depth])
        {
            printf("case '%c':\n", pms->entries[i][depth]);
            ms_do_indent(ident_level + 1);
            printf("switch (s[%d])\n", depth + 1);
            ms_do_indent(ident_level + 1);
            puts("{");
                pms->str[depth] = pms->entries[i][depth];
                ms_make_switch(pms, depth + 1, ident_level + 1);
                ms_do_indent(ident_level + 1);
                puts("default:");
                ms_do_indent(ident_level + 2);
                puts("return -1;");
                ms_do_indent(ident_level + 1);
            puts("}");
        }
        else
        {
            puts("case 0:");
            ms_do_indent(ident_level + 1);
            printf("return %d;\n", i);
            pms->checks[i] = 1;
        }
    }
}

int ms_make_identify_string_function(int count, char **entries)
{
    int i, len, max_length;
    MS_MAKE_SWITCH ms;

    max_length = 0;
    for (i = 0; i < count; ++i)
    {
        len = strlen(entries[i]);
        if (max_length < len)
            max_length = len;
    }

    ms.count = count;
    ms.str = (char *)malloc(max_length + 1);
    ms.entries = entries;
    ms.checks = (char *)calloc(count, sizeof(char));

    if (ms.str == NULL || ms.checks == NULL)
    {
        free(ms.str);
        free(ms.checks);
        return 0;
    }

    puts("int identify_string(const char *s)\n{");
        ms_do_indent(1);
        printf("switch (s[0])\n");
        ms_do_indent(1);
        puts("{");
        ms_make_switch(&ms, 0, 1);
        ms_do_indent(1);
        puts("default:");
            ms_do_indent(2);
            puts("return -1;");
        ms_do_indent(1);
    puts("}\n}");

    free(ms.str);
    free(ms.checks);
    return 1;
}
