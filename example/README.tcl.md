Compiling the library

```
> swig -tcl example.i
> gcc -c -fpic example.c example_wraper.c -I/user/include/tcl
> gcc -shared example.o exampler_wrap.o -o example.so
```

Loading the library

```
> tclsh
% load ./example.so
```
