#define JEMALLOC_SOFTBOUND_
#include "jemalloc/internal/jemalloc_internal.h"
#include <softbound.h>

NO_SB_CC JEMALLOC_EXPORT void* __softboundcets_realloc(void* ptr, size_t size) {
   void* ret_ptr = je_realloc(ptr, size);
   __softboundcets_allocation_secondary_trie_allocate(ret_ptr);
   size_t ptr_key = 1;
   void* ptr_lock = __softboundcets_global_lock;
   ptr_key = __softboundcets_load_key_shadow_stack(1);
   ptr_lock = __softboundcets_load_lock_shadow_stack(1);

   __softboundcets_store_return_metadata(ret_ptr,
                                         (char*)(ret_ptr) + size,
                                         ptr_key, ptr_lock);
   if(ret_ptr != ptr){
     __softboundcets_check_remove_from_free_map(ptr_key, ptr);
     __softboundcets_add_to_free_map(ptr_key, ret_ptr);
     __softboundcets_copy_metadata(ret_ptr, ptr, size);
   }

   return ret_ptr;
}


NO_SB_CC JEMALLOC_EXPORT void* __softboundcets_calloc(size_t nmemb, size_t size) {
   key_type ptr_key = 1 ;
   lock_type  ptr_lock = NULL;
   void* ret_ptr = je_calloc(nmemb, size);
   if(ret_ptr != NULL) {
     __softboundcets_memory_allocation(ret_ptr, &ptr_lock, &ptr_key);
     __softboundcets_store_return_metadata(ret_ptr,
                                           ((char*)(ret_ptr) + (nmemb * size)),
                                           ptr_key, ptr_lock);

     if(__SOFTBOUNDCETS_FREE_MAP) {
       //       __softboundcets_add_to_free_map(ptr_key, ret_ptr);
     }
   }
   else{
     __softboundcets_store_null_return_metadata();
   }
   return ret_ptr;
}

NO_SB_CC JEMALLOC_EXPORT void* __softboundcets_malloc(size_t size) {
  key_type ptr_key=1;
  lock_type ptr_lock=NULL;

  char* ret_ptr = (char*)je_malloc(size);
  if(ret_ptr == NULL){
    __softboundcets_store_null_return_metadata();
  } else{
    __softboundcets_memory_allocation(ret_ptr, &ptr_lock, &ptr_key);
    char* ret_bound = ret_ptr + size;
    __softboundcets_store_return_metadata(ret_ptr, ret_bound,
                                          ptr_key, ptr_lock);
    if(__SOFTBOUNDCETS_FREE_MAP) {
       //      __softboundcets_add_to_free_map(ptr_key, ret_ptr);
    }
  }
  return ret_ptr;
}


NO_SB_CC JEMALLOC_EXPORT void __softboundcets_free(void* ptr){
  /* more checks required to check if it is a malloced address */
  if(ptr != NULL){
    void* ptr_lock = __softboundcets_load_lock_shadow_stack(1);
    size_t ptr_key = __softboundcets_load_key_shadow_stack(1);
    __softboundcets_memory_deallocation(ptr_lock, ptr_key);
    if(__SOFTBOUNDCETS_FREE_MAP){
      __softboundcets_check_remove_from_free_map(ptr_key, ptr);
    }
  }
  je_free(ptr);
}
