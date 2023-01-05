

/*
 mm.c - contain LIFO form segregated list dynamic memory allocator functions
 
 //  Created by Jeon Charn on 2022/06/15 ~ 2022/06/28.
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your information in the following struct.
 ********************************************************/
team_t team = {
    /* Your student ID */
    "20201635",
    /* Your full name*/
    "Charn Jeon",
    /* Your email address */
    "jeoncharn@gmail.com",
};


// textbook의 explicit list implementation을 참고한 macro
#define ALIGNMENT 8

#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE 9000

#define MAX(x, y) ((x) > (y)? (x):(y))

#define PACK(size, alloc) ((size) | (alloc))

#define GET(p)     (*(unsigned int *)(p))
#define PUT(p,val) (*(unsigned int *)(p) = (val))

#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))


// segregated list 구현을 위한 추가적인 macro 이다.
// 총 linked list의 개수이다.
#define SEGLEN 8

// FREE list에서 다음과 이전 block을 파악하는 macro 이다.
#define NEXT_FREE(bp) (*(void**)(bp + WSIZE))
#define PREV_FREE(bp) (*(void**)(bp))

// prologue block -> 맨 앞의 allocated 표시, alignment를 도와준다.
void* heap_listp;

// size 별 explicit list의 root가 될 seg_list 이다.
// array를 사용하지 못하기 때문에, double pointer을 사용하여 구현했다.
void** seg_list;

// mm_~~ function을 위해 추가적으로 구현한 함수들이다.
// textbook을 참고했다.
static void *extend_heap(size_t words);
static void *coalesce(void *bp);
static void insert_block(void* bp, size_t size);
static void remove_block(void *bp);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);


/*
* mm_init - initialize the malloc package.
 seg_list을 NULL로 설정한다.
 prologue, epilogue을 설정하며 초기 block을 CHUNKSIZE 만큼 잡는다.
 
 실제 heap 영역에는 seg_list / prologue / CHUNKSIZE block / epilogue 순서로 존재한다.
 
*/

int mm_init(void)
{

    // 전역 변수로 array를 사용할 수 없기 때문에, double pointer에 mem_sbrk로 할당을 받는다.
    // 할당 받는 size는 SEGLEN * WSIZE 이다.
    if ((seg_list = mem_sbrk(SEGLEN * WSIZE)) == (void *)-1)
    {
        return -1;
    }
    
    // 각 seg_list의 root들을 NULL 로 초기화한다.
    for(int i=0; i<SEGLEN; i++){
        seg_list[i] = NULL;
    }
    
    /* Create the initial empty heap */
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
    {
        return -1;
    }
    
    PUT(heap_listp, 0);
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));
    heap_listp += (2*WSIZE);
    
    // 초기 block의 할당
    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
    {
        return -1;
    }
    
    return 0;
}

/*
* mm_malloc - Allocate a block by incrementing the brk pointer.
*     Always allocate a block whose size is a multiple of the alignment.
*/

void *mm_malloc(size_t size)
{
    size_t asize = ALIGN(size + SIZE_T_SIZE);
    size_t extendsize;
    char *bp;
        
    if(size == 0){
        return NULL;
    }
    
    // 이미 존재하는 block에서 찾을 수 있는 경우
    if ((bp = find_fit(asize)) != NULL)
    {
        place(bp, asize);
        return bp;
    }
    
    // 새로운 block을 잡는다. 크기는 asize와 CHUNKSIZE 중 최대값으로 설정한다.
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
    {
        return NULL;
    }
    
    // 해당 block을 size에 맞게 분할한다.
    place(bp, asize);
    return bp;
}

/*
* mm_free - Freeing a block does nothing.
*/
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    // header, footer 의 allocated bit = 0 으로 설정한다.
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));

    // coalescing 을 수행하며 free list에 다시 삽입한다.
    coalesce(ptr);
}

/*
* mm_realloc - Implemented simply in terms of mm_malloc and mm_free
*/

void *mm_realloc(void *ptr, size_t size)
{
    void *newptr;
    size_t copySize;

    // 이전 pointer이 없다면, malloc을 수행한다.
    if(ptr == NULL){
        return mm_malloc(size);
    }
    
    // size = 0 이라면 free를 수행한다.
    if(size == 0){
        mm_free(ptr);
        return NULL;
    }
    
    // 해당하는 block의 size가 충분한 경우
    if(GET_SIZE(HDRP(ptr)) >= ALIGN(size + SIZE_T_SIZE)){
        return ptr;
    }
    
    // 해당하는 block의 size가 충분하지 않은 경우
    // size에 적합한 새로운 block을 할당한다.
    newptr = mm_malloc(size);
    
    if (newptr == NULL)
        return NULL;
    copySize = GET_SIZE(HDRP(ptr));

    // 이전 data를 새로 할당한 block에 copy한다.
    memcpy(newptr, ptr, copySize);
    mm_free(ptr);
    return newptr;
}


// mem_sbrk로 size를 늘리며, free list에 추가한다.
static void *extend_heap(size_t words)
{
   char *bp;
   size_t size;

   /* Allocate an even number of words to maintain alignment */
   size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
   if ((long)(bp = mem_sbrk(size)) == -1)
   {
       return NULL;
   }
   /* Initialize free block header/footer and the epilogue header */
   PUT(HDRP(bp), PACK(size, 0));         /* free block header */
   PUT(FTRP(bp), PACK(size, 0));         /* free block footer */
   PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue */

   /* Coalesce if the previous block was free */
   return coalesce(bp);
}

// 어떠한 bp에 대해, 앞뒤의 free를 확인하며, 이를 적절한 list의 위치에 대입하는 함수이다.
// 맨 앞과 맨 뒤에 Prologue, Epilogue 가 존재하기 때문에, 별다른 에러가 발생하지 않는다.
static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if(prev_alloc && next_alloc){
        insert_block(bp, size);
        return bp;
    }
    
    else if (prev_alloc && !next_alloc){
        remove_block(NEXT_BLKP(bp));

        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));

    }
    else if (!prev_alloc && next_alloc){
        remove_block(PREV_BLKP(bp));

        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    else{
        remove_block(PREV_BLKP(bp));
        remove_block(NEXT_BLKP(bp));

        size += (GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp))));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    
    insert_block(bp, size);
    return bp;
}

// 해당 size list에 LIFO 형식의 삽입
static void insert_block(void *bp, size_t size){
    int index = 0;
    size >>= 4;
    
    while ((index < SEGLEN - 1) && (size > 1)){
        size >>= 1;
        index++;
    }

    // linked list에 아무 원소도 존재하지 않는 경우
    if(seg_list[index] == NULL){
        seg_list[index] = bp;
        PREV_FREE(bp) = NULL;
        NEXT_FREE(bp) = NULL;
    }
    
    // 다른 원소가 존재하는 경우
    else{
        NEXT_FREE(bp) = seg_list[index];
        PREV_FREE(seg_list[index]) = bp;
        PREV_FREE(bp) = NULL;
        seg_list[index] = bp;
    }
    
    return;
}


// free list에서 해당 bp를 제거하는 함수
static void remove_block(void *bp){
    
    // 해당 bp 가 존재하는 seg_list 상 index를 파악한다.
    int index = 0;
    size_t size = GET_SIZE(HDRP(bp));
    
    // 16~31까지 index = 0, 32~63 index = 1
    size >>= 4;

    while ((index < SEGLEN - 1) && (size > 1)) {
        size >>= 1;
        index++;
    }

    // bp 가 마지막이 아닌 경우
    // 맨 앞이 아닌 경우
    if (NEXT_FREE(bp) != NULL){
        if (PREV_FREE(bp) != NULL){
           PREV_FREE(NEXT_FREE(bp)) = PREV_FREE(bp);
           NEXT_FREE(PREV_FREE(bp)) = NEXT_FREE(bp);
        }
        else{
           PREV_FREE(NEXT_FREE(bp)) = NULL;
           seg_list[index] = NEXT_FREE(bp);
       }
    }
    //bp 가 마지막인 경우
    else{
       if(PREV_FREE(bp) != NULL){
           NEXT_FREE(PREV_FREE(bp)) = NULL;
       }else{
           seg_list[index] = NULL;
       }
   }
   return;
}

// 이미 존재하는 seg_list 에서 size에 맞는 block을 찾는다.
static void *find_fit(size_t asize)
{
    void* bp;
    void* searchlist;
    
    int index = 0;
    size_t searchsize = asize;
    searchsize = searchsize - 1;
    searchsize >>= 3;

    while ((index < SEGLEN - 1) && (searchsize > 1)) {
        searchsize >>= 1;
        index++;
    }
    
    // 마지막 list에서 찾지 않는 경우, LIFO를 수행한다.
    for(index; index < SEGLEN - 1; index++){
        if(seg_list[index] != NULL){
            bp = seg_list[index];
            return bp;
        }
    }
    
    // seg_list의 마지막 linked list에서 검색하는 경우
    searchlist = seg_list[SEGLEN-1];
    while(searchlist != NULL){
        if(GET_SIZE(HDRP(searchlist)) >= asize){
            bp = searchlist;
            return bp;
        }
        searchlist = NEXT_FREE(searchlist);
    }

   return NULL; /* no fit */

}

// block의 남는 공간이 16 byte 이상인 경우, 분할을 수행하는 함수이다.
// 분할한 부분을 다시 coalescing 하며 free list에 삽입해야 한다.
static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));
    
    // free list에서 bp를 제거한다.
    
    remove_block(bp);
    
    if ((csize - asize) >= 16)
    {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
        // 나머지 부분을 다시 free list에 추가한다.
        coalesce(bp);
    }
    
    else
    {
        // allocated bit만 할당한다.
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
    }
    
    return;
}
