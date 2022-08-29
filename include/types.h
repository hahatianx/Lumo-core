
#if defined(__i386__)
typedef uint32_t ptr_t;
#elif defined(__x86_64__) || defined(__ia64__)
typedef unsigned long long uint64_t;
typedef uint64_t ptr_t;
#endif

