
#include "./funcs.inc"
#define TYPE_IS_INT
//#define TYPE_IS_SHORT
int main()
{
  TYPE A, B;
  printf("Input A, B: \n");
#ifdef TYPE_IS_INT
  scanf("%d %d", &A, &B);
#elif defined(TYPE_IS_SHORT)
  scanf("%hd %hd", &A, &B);
#else
  scanf("%lld %lld", &A, &B);
#endif

  if ((A < 0) && (B < 0))
  {
    printf("Input correct A and B\n");
    return 0;
  }
  TYPE a_min, b_max;
  printf("Input Enter the left and right generation range: \n");
#ifdef TYPE_IS_INT
  scanf("%d %d", &a_min, &b_max);
#elif defined(TYPE_IS_SHORT)
  scanf("%hd %hd", &a_min, &b_max);
#else
  scanf("%lld %lld", &a_min, &b_max);
#endif
  if (a_min >= b_max)
  {
    printf("Input correct a_min < b_max\n");
    return 0;
  }

  printf("The original matrix:\n");
  TYPE **ar = (TYPE **)malloc(A * sizeof(TYPE *));
  if (ar == NULL)
  {
    printf("Error: Memory allocation failed\n");
    return 1;
  }

  for (TYPE i = 0; i < A; i++)
  {
    ELEM(ar, i) = (TYPE *)malloc((B + 1) * sizeof(TYPE));
    if (ELEM(ar, i) == NULL)
    {
      printf("Error: Memory allocation failed\n");
      for (TYPE j = 0; j < i; j++)
      {
        free(ELEM(ar, j));
      }
      free(ar);
      return 1;
    }
  }

  for (TYPE i = 0; i < A; i++)
  {
    ELEM(ar, i)
    [0] = B;
  }

  srand(time(NULL));
  for (TYPE i = 0; i < A; i++)
  {
    for (TYPE j = 1; j < B + 1; j++)
    {
      ELEM(ar, i)
      [j] = rand() % (b_max - a_min + 1) + a_min;
    }
  }

  for (TYPE i = 0; i < A; i++)
  {
    for (TYPE j = 0; j < ELEM(ar, i)[0] + 1; j++)
    {
#ifdef TYPE_IS_INT
      printf("%d ", ELEM(ar, i)[j]);
#elif defined(TYPE_IS_SHORT)
      printf("%hd ", ELEM(ar, i)[j]);
#else
      printf("%lld ", ELEM(ar, i)[j]);
#endif
    }
    printf("\n");
  }

  TYPE K;
  printf("Input index element: \n");
#ifdef TYPE_IS_INT
  scanf("%d", &K);
#elif defined(TYPE_IS_SHORT)
  scanf("%hd", &K);
#else
  scanf("%lld", &K);
#endif

  TYPE N;
  printf("Enter the number of numbers you want to add: \n");
#ifdef TYPE_IS_INT
  scanf("%d", &N);
#elif defined(TYPE_IS_SHORT)
  scanf("%hd", &N);
#else
  scanf("%lld", &N);
#endif

  TYPE M;
  printf("Enter the offset for the zeros: \n");
#ifdef TYPE_IS_INT
  scanf("%d", &M);
#elif defined(TYPE_IS_SHORT)
  scanf("%hd", &M);
#else
  scanf("%lld", &M);
#endif

  for (TYPE i = 0; i < A; i++)
  {
    if (i % 4 == 0)
    {
#ifdef DELETE_ELEM
      delete_element(ELEM(ar, i), K);
#else
      delete_last_elements(ELEM(ar, i), K);
#endif
    }
    else if (i % 4 == 1)
    {
      ELEM(ar, i) = append(ELEM(ar, i), K, N, a_min, b_max);
    }
    else if (i % 4 == 2)
    {
      cyclicShiftZeroes(ELEM(ar, i), M);
    }
    else
    {
#ifdef SEARCH_FIRST
      search_first(ELEM(ar, i));
#else
      search_last(ELEM(ar, i));
#endif
    }
  }
  printf("The final matrix: \n");
  for (TYPE i = 0; i < A; i++)
  {
    for (TYPE j = 0; j < ELEM(ar, i)[0] + 1; j++)
    {
      if (j == ELEM(ar, i)[0])
      {
#ifdef TYPE_IS_INT
        printf("%d\n", ELEM(ar, i)[j]);
#elif defined(TYPE_IS_SHORT)
        printf("%hd\n", ELEM(ar, i)[j]);
#else
        printf("%lld\n", ELEM(ar, i)[j]);
#endif
        break;
      }
#ifdef TYPE_IS_INT
      printf("%d ", ELEM(ar, i)[j]);
#elif defined(TYPE_IS_SHORT)
      printf("%hd ", ELEM(ar, i)[j]);
#else
      printf("%lld ", ELEM(ar, i)[j]);
#endif
    }
    printf("\n");
  }

  for (TYPE i = 0; i < A; i++)
  {
    free(ELEM(ar, i));
  }
  free(ar);

  return 0;
}