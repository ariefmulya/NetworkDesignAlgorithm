#include <stdio.h>

double erlangb_blocking_prob(double erlang, double capacity)
{
  double i = 1.00;
  double blocking = 1.00;

  for ( ; i <= capacity; i++) {
    blocking = erlang*blocking / ((erlang*blocking)+i);
    /* printf(" --- current blocking: %lf --- \n", blocking); */
  }

  return blocking;
}

double erlangb_required_capacity(double erlang, double gos)
{
  double blocking = 0.0;
  double capacity = erlang-1.0;

  do {
    blocking = erlangb_blocking_prob(erlang, capacity);
    capacity++;
    /* printf(" --- current b/c: %lf/%lf ---\n", blocking, capacity); */
  } while (blocking > gos);

  return capacity;
}

double erlangb_offered_erlang(double capacity, double gos)
{
  double blocking = 0.0;
  double erlang = capacity+1.0;

  do {
    blocking = erlangb_blocking_prob(erlang, capacity);
    erlang--;
    /* printf(" --- current b/e: %lf/%lf ---\n", blocking, erlang); */
  } while (blocking > gos);

  return erlang;
}

double erlangb_overflow_traffic(double erlang, double capacity)
{
  double blocking = 0.0;
  double overflow = 0.0;

  blocking = erlangb_blocking_prob(erlang, capacity);

  return erlang * blocking;
}

int main(void)
{
  double erlang = 0.0;
  double capacity = 30.0;
  double gos = 0.02;

  for (; erlang <= capacity; erlang++) {
    printf("Erlang: %lf, Capacity: %lf, Blocking (%): %lf\n", erlang, capacity, erlangb_blocking_prob(erlang, capacity)*100.0);
  }

  erlang = 21.0;
  printf("Erlang: %lf, GOS: %lf, Capacity: %lf\n", erlang, gos, erlangb_required_capacity(erlang, gos));

  capacity = 30.0;
  printf("Capacity: %lf, GOS: %lf, Erlang: %lf\n", capacity, gos, erlangb_offered_erlang(capacity, gos));


  erlang = 15.0;
  for (; erlang <= capacity; erlang++) {
    printf("Erlang: %lf, Capacity: %lf, Overflow: %lf\n", erlang, capacity, erlangb_overflow_traffic(erlang, capacity));
  }

  return 0;
}
