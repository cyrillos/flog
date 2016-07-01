## The super fast printf-like logging engine

printf() spends the most part of time in formating strings. The idea of
**flog** is to save raw messages in a binary format as fast as possible and
then decode them into human readable format from outside a program.

## How fast is it

Here is a few numbers to compare flog with dprintf

```
$ time ./flog -m dprintf -i 1000000 -o /tmp/raw.log

real	0m1.155s
user	0m0.616s
sys	0m0.539s
```

```
$ time ./flog -i 1000000 -o /tmp/raw.log

real	0m0.164s
user	0m0.089s
sys	0m0.075s
```
