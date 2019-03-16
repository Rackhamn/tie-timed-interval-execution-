# TIE (timed interval execution)
TIE is a background timer that executes any given commands at regular intervals.

## Detail
TIE is a small and simple tool to auto run any command via your terminal.
It allows for you to set a timing interval and however many commands you want.

### Compiling
Nothing hard or complicated.
On my machine TIE is compiled with gcc and its C89 standard.
```
gcc tie.c -std="c89" -o tie
```
Using clang should not be a problem either.

### More Detail
TIE is not very portable yet.
It compiles under linux (Mint Cinnamon 18.3) atleast but probably not all unix or freebsd distros.

## How to use TIE
Once you have compiled tie you can use it like this.
```
./tie [time type] [sleep time] [count time] [commands]
```
Example:
```
./tie -mm 10 99 "echo I'm Using TIE!"
-mm = minutes
10 = how many minutes inbetween commands
99 = how many times should we sleep
```

### Options:
```
-ns = nanoseconds
-ms = milliseconds
-ss = seconds
-mm = minutes
-hh = hours
-dd = days
```
