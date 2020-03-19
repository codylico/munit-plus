# µnit-plus

This is an unofficial port of the `µnit` unit testing library to C++ 2011.
Features include:
 * API similar to the original library
 * Proper handling of exceptions
 * Templated functions for randomizing trivial instances
 * Support for user-defined comparison operators for assertions
 * Support for custom formatters for user-defined classes

The license remains MIT.

### Build status for µnit-plus
[![Build status](https://travis-ci.com/codylico/munit-plus.svg?branch=cxx11)](https://travis-ci.com/github/codylico/munit-plus)
[![Windows build status](https://ci.appveyor.com/api/projects/status/2g4e5b3fferv9hmw?svg=true)](https://ci.appveyor.com/project/codylico/munit-plus/branch/cxx11)

Original README continues below.

## µnit (from original)

µnit is a small but full-featured unit testing framework for C.  It has
no dependencies (beyond libc), is permissively licensed (MIT), and is
easy to include into any project.

For more information, see
[the µnit web site](https://nemequ.github.io/munit).

[![Build status](https://travis-ci.org/nemequ/munit.svg?branch=master)](https://travis-ci.org/nemequ/munit)
[![Windows build status](https://ci.appveyor.com/api/projects/status/db515g5ifcwjohq7/branch/master?svg=true)](https://ci.appveyor.com/project/quixdb/munit/branch/master)

## Features

Features µnit currently includes include:

 * Handy assertion macros which make for nice error messages.
 * Reproducible cross-platform random number generation, including
   support for supplying a seed via CLI.
 * Timing of both wall-clock and CPU time.
 * Parameterized tests.
 * Nested test suites.
 * Flexible CLI.
 * Forking
   ([except on Windows](https://github.com/nemequ/munit/issues/2)).
 * Hiding output of successful tests.

Features µnit does not currently include, but some day may include
(a.k.a., if you file a PR…), include:

 * [TAP](http://testanything.org/) support; feel free to discuss in
   [issue #1](https://github.com/nemequ/munit/issues/1)

### Include into your project with meson

In your `subprojects` folder put a `munit.wrap` file containing:

```
[wrap-git]
directory=munit
url=https://github.com/nemequ/munit/
revision=head
```

Then you can use a subproject fallback when you include munit as a
dependency to your project: `dependency('munit', fallback: ['munit', 'munit_dep'])`

## Documentation

See [the µnit web site](https://nemequ.github.io/munit).

Additionally, there is a heavily-commented
[example.c](https://github.com/nemequ/munit/blob/master/example.c) in
the repository.
