#include <stdio.h>

#define MAX 100

int a[MAX];
int rand_seed = 91;

/* FROM K&R

   Returns a random number between 0 and 32767.
*/
int rand() {
  rand_seed = rand_seed * 1103515245 + 12345;
  return (unsigned int) (rand_seed / 65536) % 32768;
}

int main(void) {
  int i, t, x, y;

  /* Fill Array */
  for (i=0; i < MAX; ++i) {
    a[i] = rand();
  }

  /* Bubble Sort the array */
  for (x=0; x < MAX - 1; ++x) {
    for (y=0; y < MAX - x - 1; ++y) {
      if (a[y] > a[y+1]) {
        t = a[y]; /* temporarily store the original variable */
        a[y] = a[y+1]; /* copy the smaller variable down one index */
        a[y+1] = t; /* place temp variable into larger index */
      }
    }
  }

  /* Print sorted array */
  printf("----------------------\n");
  for (i=0; i < MAX; ++i) {
    printf("%d\n", a[i]);
  }

  return 0;

}
