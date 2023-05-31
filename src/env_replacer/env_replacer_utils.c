
#include "../env_replacer/env_replacer.h"
#include <string.h>


bool is_uppercase(char *s)
{
    size_t i = 0; 

    while (s[i] != '\0')
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            break;
        i++;
    }
    if (i == strlen(s))
        return (true);
    else
        return (false);
}

bool has_env_char(char *s, int *n_envs)
{
    int i = 0;
    int j = 0;

    while (s[i] != '\0')
    {
        if (s[i] == '$')
            j++;
        i++;
    }
    if (j >= 1)
    {
        *n_envs = j;
        return (true);
    }
    return (false);
}

bool check_if_quotes(char *s)
{
    if (s[0] == '\'')
        return (false);
    if (s[0] == '"')
    {
        return (true);    
    }
    if (s[0] != '"')
    {
        if (strrchr(s, '\''))
        {
            if (strrchr(s, '$'))
            {
                return (false);
            }
        }     
        else
            return (true);        
    }
    if (s[0] == '$')
    {
        if (strrchr(s, '\''))
        {
            if (strrchr(s, '$'))
            {
                return (false);
            }
        }     
        else
            return (true);        
    }
    return(false);
}

bool check_quotes(char *s)
{
    if (s[0] != '\'' || s[0] == '"')
    {
        if (check_if_quotes(s))
            return (true); 
    }
    return (false);
}

bool can_change(char *s, int *n_envs)
{
    if (check_quotes(s))
    {
        if (has_env_char(s, n_envs))
        {
            return (true);
        }
    } 
    return (false);
}
