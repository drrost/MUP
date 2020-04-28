void mx_printchar(char c);

void mx_printint(int n) {
    long work = n;
    if (work < 0) {
        mx_printchar('-');
        work = -work;
    }
    if (work > 9)
        mx_printint(work / 10);
    mx_printchar(work % 10 + 48);
}
