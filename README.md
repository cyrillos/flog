## The super fast printf-like logging engine

printf() spends the most part of time in formating strings. The idea of
**flog** is to save raw messages in a binary format as fast as possible and
then decode them into human readable format from outside a program.
