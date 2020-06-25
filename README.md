
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

The full math problem is called [Prepsosterous Primes](http://www.zacharycormack.net/challenge-of-jun-22-2020/ "zacharycormack.net")

This project contains three programs: `CALC`, `READ`, and `MOVE`.

`CALC` calculates the prime connected set of _N_ and S(_N_), and records it in the `log.hex` file.
`READ` reads the `log.hex` file.
`MOVE` illustrates what a prime step is interactively.

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

## MOVE
In the interactive move program, you choose a number to start at.
Try _23_ for fun!
You are then told which prime you are at currently and asked which number to step to next.
If you choose a number not prime connected to the number you are currently at, you will be asked again.
This not only illustrates what a prime connection *is*, but the *maze-like* structure they form, and the methods used in the `CALC` program.
In fact, this program is nearly identical to the `CALC` program at it's core, with only a few changes to the `step` function and user interface.

## LOG
The `log.hex` file is, as can be expected, a log of all the calculations done by the `PRIME_STEP` program.
The `log.hex` file is not included in the repository.
This is kept because the `PRIME_STEP` function takes a while to calculate, but it's results can be easily stored for later convenience.
To read the `log.hex` file, a `READ` program is available, and converts to decimal automatically.
The format in which the log is stored also works with all hexadecimal readers, like `xxd`, though it is less effective than the `READ` program.
