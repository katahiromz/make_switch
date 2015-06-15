#ifndef KATAHIROMZ_MS_MAKE_SWITCH_H_
#define KATAHIROMZ_MS_MAKE_SWITCH_H_ /* version */ 1

#define MS_MAX_STRING_LEN 32
#define MS_TAB_WIDTH -1

typedef struct MS_MAKE_SWITCH
{
    int count;
    char *str;
    char **entries;
    char *checks;
} MS_MAKE_SWITCH;

void ms_do_indent(int n);
void ms_make_switch(MS_MAKE_SWITCH *pms, int depth, int ident_level);
int ms_make_identify_string_function(int count, char **entries);

#endif  /* ndef KATAHIROMZ_MS_MAKE_SWITCH_H_ */
