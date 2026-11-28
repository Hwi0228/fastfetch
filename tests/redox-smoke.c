#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>

static int fail(const char *message)
{
    fprintf(stderr, "FAIL: %s\n", message);
    return 1;
}

int main(void)
{
    struct utsname system_info;
    if (uname(&system_info) != 0)
        return fail("uname() failed");

    printf("sysname=%s\n", system_info.sysname);
    printf("release=%s\n", system_info.release);
    printf("machine=%s\n", system_info.machine);

    if (strcmp(system_info.sysname, "Redox") != 0)
        return fail("uname() did not identify Redox");

    long page_size = sysconf(_SC_PAGESIZE);
    long physical_pages = sysconf(_SC_PHYS_PAGES);
    long online_cpus = sysconf(_SC_NPROCESSORS_ONLN);

    printf("page_size=%ld\n", page_size);
    printf("physical_pages=%ld\n", physical_pages);
    printf("online_cpus=%ld\n", online_cpus);

    if (page_size <= 0)
        return fail("sysconf(_SC_PAGESIZE) returned an invalid value");
    if (physical_pages <= 0)
        return fail("sysconf(_SC_PHYS_PAGES) returned an invalid value");
    if (online_cpus <= 0)
        return fail("sysconf(_SC_NPROCESSORS_ONLN) returned an invalid value");

    struct timespec monotonic_time;
    if (clock_gettime(CLOCK_MONOTONIC, &monotonic_time) != 0)
        return fail("clock_gettime(CLOCK_MONOTONIC) failed");

    printf("monotonic_seconds=%lld\n", (long long) monotonic_time.tv_sec);
    printf("PASS: Redox POSIX runtime probe\n");
    return 0;
}
