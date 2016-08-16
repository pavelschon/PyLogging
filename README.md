# PyFormat - boost::format python module #

**PyLogging** is fast and lightweight logging module and can be used together with PyFormat module.

The module is low-level and does not offer features like *lineno*, *asctime* etc.

The module is thread-safe and is compatible with Python 2.x and Python 3.x versions.


## Requirements ##

1. C++ compiler

2. CMake

3. Python headers (2.x or 3.x)

4. Boost libraries


## Build ##

```
$ mkdir build
$ cd build
$ cmake ..
$ make package
$ dpkg -i pylogging-0.1.0-Linux.deb
```

## Logger ##

*Logger* can have zero or more handlers attached. *Handler* can be attached multiple loggers.

## Handlers ##

1. *NullHandler* - no output

2. *StdOutHandler* - output to std::wout

2. *StdErrHandler* - output to std::werr

3. *StdLogHandler* - output to std::wlog

4. *FileHandler* - output to std::wofstream

Output in the handler is synchronized using mutex.

## Run ##


```
FIXME
```