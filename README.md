# labs for operating systems in C

## First lab

The first lab is located in `one_cond_monitor` directory.

It is a monitor for operating systems linux has been implemented using `pthread`.

## Second lab

Build:

```
gcc -std=c99 -o server -D_POSIX_C_SOURCE=200809L -D_POSIX_PTHREAD_SEMANTICS main.c && ./server
```

Connect client (For disconnect send any symbol (two bytes)):

```
telnet localhost 1234
```


Send signal:

```
kill -1 <SERVER_PID>
```