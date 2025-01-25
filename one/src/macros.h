#ifndef MACROS_H
#define MACROS_H



#define ARRAY_COUNT(a) (sizeof(a)/sizeof(*(a)))

#define ASSERT(a) if(!(a)) (*(int*)0 = 0)

#define CLAMP(l,x,r) (((x)<(l))?(l):(((x)>(r))?(r):(x)))

#define MAX(l,r) (((l)>(r))?(l):(r))

#define MIN(l,r) (((l)<(r))?(l):(r))

#define PASTE_(s,t) s##t
#define PASTE(s,t) PASTE_(s,t)

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)



#endif /* MACROS_H */