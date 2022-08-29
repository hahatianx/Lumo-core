
#define RUN_TEST(func, description)                                                  \
    do {                                                                             \
        printf("----------- %s starts here \n", description);                        \
        func;                                                                        \
        printf("----------- test ends \n");                                          \
    } while(0)                                                                       

#define ASSERT_TEST(e, description)                                                  \
    do {                                                                             \
        printf("%s\t: ", description);                                               \
        assert(e);                                                                   \
        printf("pass\n");                                                            \
    } while(0)                                                                       