/**************************************************************
  Tempos:                                                     *
    Sequencial: 0m4.045s                                      *
    Paralelo:                                                 *
      static: 0m2.552s                                        *
        speedup = 1.58                                        *
      dynamic: 0m2.587s                                       *
        speedup = 1.56                                        *
      guided: 0m2.537s                                        *
        speedup = 1.59                                        *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <omp.h>

int sieveOfEratosthenes(int n){
  // Create a boolean array "prime[0..n]" and initialize
  // all entries it as true. A value in prime[i] will
  // finally be false if i is Not a prime, else true.
  int primes = 0;
  bool *prime = (bool*) malloc((n+1)*sizeof(bool));
  int sqrt_n = sqrt(n);

  memset(prime, true,(n+1)*sizeof(bool));

  for (int p=2; p <= sqrt_n; p++){
    // If prime[p] is not changed, then it is a prime
    if (prime[p] == true){
      // Update all multiples of p
      #pragma omp parallel for
      for (int i=p*2; i<=n; i += p)
        prime[i] = false;
    }
  }

  // count prime numbers
  #pragma omp parallel for reduction (+ : primes) schedule(guided, 100)// Aplicação do padrão reduce
  for (int p=2; p<=n; p++)
    if (prime[p])
      primes++;

  return(primes);
}

int main(){
  int n = 100000000;
  printf("%d\n",sieveOfEratosthenes(n));
  return 0;
}
