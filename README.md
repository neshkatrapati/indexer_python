#Indexer-Python

## What ?
Given a large text file, indexer makes an index and stores it in binary. When a specific line is needed, it hits the index first, then the original file.

Indexer Python is a Cython wrapper over neshkatrapati/indexer.

## How to ?
Install Cython before this.
> #### Install
    $ python setup.py install
    (or)
    $ pip install indexer_python

See tests/ for examples
