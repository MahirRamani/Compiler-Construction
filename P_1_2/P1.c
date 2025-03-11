#include <stdio.h>

int validate_string(const char *str)
{
    int i = 0;

    while (str[i] == 'a')
    {
        i++;
    }

    if (str[i] == 'b' && str[i + 1] == 'b')
    {
        i += 2;
    }
    else
    {
        return 0;
    }

    if (str[i] == '\0')
    {
        return 1;
    }

    return 0;
}

int main()
{
    char *test_strings[] = {
        " ", "abb", "aabb", "ababb", "ab", "bbb", "bba", "aabbb"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++)
    {
        if (validate_string(test_strings[i]))
        {
            printf("'%s' is VALID\n", test_strings[i]);
        }
        else
        {
            printf("'%s' is INVALID\n", test_strings[i]);
        }
    }
    getchar();
    return 0;
}