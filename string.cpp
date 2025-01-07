static unsigned long string_length(char* str)
{
    char* string = str;
    while(*string != '\0')
        string++;
    return string - str;
}
