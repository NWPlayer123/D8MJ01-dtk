typedef struct DestructorChain {
    struct DestructorChain* next;
    void* destructor;
    void* object;
} DestructorChain;

DestructorChain* __global_destructor_chain;

void __destroy_global_chain(void) {
    DestructorChain* gdc;
    while ((gdc = __global_destructor_chain) != 0) {
        __global_destructor_chain = gdc->next;
        (((void (*)(void*, short))gdc->destructor)(gdc->object, -1));
    }
}

#ifdef __MWERKS__
__declspec(section ".dtors") const void* __destroy_global_chain_reference = __destroy_global_chain;
#endif
