# c-containers
Uses memory container from the following repo: https://github.com/FatalSleep/null-terminated-memory

CVector is a derivative of iDestinyKK's CN_Vec: https://github.com/iDestyKK/CN_Vec

Dynamic memory containers for C:
- CBase (generic container)
- CVector
- CStack
- CString (Not using CBase)

This library exploits how the C compiler assigns memory addresses to structs in order to create generic containers. The compiler will always assign memory addresses for members of a struct in the same order they were initialized. If we take two different structs and give them the same starting variables in the same order, essentially C can't tell the difference when we cast between them.

For example:
```C
typedef struct some_base {
  int x, y, z;
} base;

typedef struct some_container {
  int x, y, z;
  void* memory;
} container;
```
If we cast container -> base, we can use container as as the generic base type since they have the same beginning variables. The variable names don't even matter as long as the types of the variables are the same, in the same order.
```C
container* var = (container*) malloc(sizeof(container));
base* generic = (base*) var;

printf("%i%c", generic->x, '\n');
printf("%i%c", generic->y, '\n');
printf("%i%c", generic->z, '\n');
```
Voila, evil hack for generic containers.
