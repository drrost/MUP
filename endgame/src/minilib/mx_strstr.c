int mx_strlen(const char *s);
int mx_strncmp(const char *s1, const char *s2, int n);

char *mx_strstr(const char *s1, const char *s2) {

    int len1 = mx_strlen(s1);
    int len2 = mx_strlen(s2);

    if (len1 < len2)
        return 0;

    for (int i = 0; i < len1 - len2; i++) {
        if (mx_strncmp(s1, s2, len2) == 0) {
            return (char *)s1;
        }
        s1++;
    }

    return 0;
}
