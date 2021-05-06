# Thread-safe stack

A small implementation of a thread-safe stack written in C++.

Compile using the `Makefile` on a UNIX system.

    $ make

## How to use this implementation

Run a basic program with some threads

    $ make run-basic

**Run all tests**

You may want to run it to check the implementation.

    $ make test all-operations

**Run test by name**

You can test a specific stack operation (unit test)

    $ make test <testname>

Example: Run a unit test for the single pop operation

    $ make test single-pop

**List of test names**

These are all the posible test:

- single-pop
- single-push
- correct-items
- multiple-pop
- multiple-push

**Clean**

Clean executable files

    $ make clean