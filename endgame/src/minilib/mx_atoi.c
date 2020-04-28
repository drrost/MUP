#include <stdbool.h>

bool mx_isdigit(int c);
bool mx_isspace(int c);

int mx_atoi(const char *str) {
    while (mx_isspace(*str)) {
        str++;
    }
    bool isNegative = 0;
    bool hasSign = 0;
    if (str[0] == '-' || str[0] == '+') {
        isNegative = str[0] == '-';
        str++;
        hasSign = 1;
    }

    int result = 0;
    while (*str != '\0') {
        if (mx_isspace(*str)) {
            if (result != 0) {
                return result;
            }
            if (result == 0 && hasSign) {
                return 0;
            }
            str++;
            continue;
        } else if (mx_isdigit(*str)) {
            result *= 10;
            result += *str - '0';
        } else {
            return result;
        }
        str++;
    }
    if (isNegative) {
        result = -result;
    }
    return result;
}
