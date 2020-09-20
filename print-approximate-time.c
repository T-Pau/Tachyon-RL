void print_approximate_time(uint32_t ms) {
    if (ms < 120000) {
        printf("%lu seconds", (ms + 500) / 1000);
    }
    else {
        printf("%lu minutes", (ms + 30000) / 60000);
    }
}
