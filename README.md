
# PRIME_STEP
![LOGO](http://www.zacharycormack.net/wp-content/uploads/2019/01/Logo2-1-300x179.png "zacharycormack.net")

> The use of this software is dictated by the __LICENSE__ file.

This project is relevant to a certain mathematical problem:

> Let a prime factor connection be a connection from two whole numbers _A_ and _B_, such that:
> 
> * _A_ and _B_ share a common prime factor _C_
> * _A_ plus _C_ equals _B_
> * _A_ divided by _C_ is not prime
> 
> For any whole number N, let the prime connected set of _N_ be the set of all whole numbers that satisfy the following:
> 
> * For any number _X_ in this set, _N_ is part of its prime connected set
> * All numbers prime connected to _N_ are in this set
> * This set is the *minimum possible size* given the first two requirements
> 
> Let S(_N_) be the size of the prime connected set of N

This project contains two programs:
`CALC`, which calculates the prime connected set of _N_ and S(_N_), and records it in the `log.hex` file, and
`READ`, which reads the `log.hex` file.

## CALC
This program calculates the number of primes in the prime connected set of _N_ in a very straightforward way:
> Have some unsigned _X_, which starts of equal to _N_.
> Change _X_ to a number prime connected to _X_.
> If _X_ is not in the prime connected set of _N_ yet, append it.
> Repeat __0x4000000__ times.
Thus calculating every item in the prime connected set of _N_.

This is then recorded to the `log.hex` file, in little endian.
Optionally, you may immediately list all of the entries, but for long lists it is better to use the READ program.

## READ
This program simply reads the little endian in the `log.hex` file.
Each entry is terminated by a `0`, and each `unsigned` logged has 2 bytes.
The log reader will count the entries and ask if you would like to list any of them.
When you list, you are offered the option to concatenate if the entry exceeds 64 entries.
Typically you should do this.

# LOG
The `log.hex` file is, as can be expected, a log of all the calculations done by the `PRIME_STEP` program.
This is kept because the `PRIME_STEP function takes a while to calculate, but it's results can be easily stored for later convenience.

The `log.hex` file currently contains the entry for 23.
