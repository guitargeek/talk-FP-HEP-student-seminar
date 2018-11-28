# How you in HEP can benefit from Functional Programming

Slides and code corresponding to the talk given at the LLR student seminar on 28. November 2018

## Summary

Functional programming (FP) is a rather academic topic within computer science.
When this topic is raised, you might perhaps think of wizard-like looking men
who tell you that you should use Haskell. However, the concepts developed in
the FP community like first-class and higher-order functions, pure functions
and advanced type systems can also be used to make your scientific C++ or
Python code more robust, readable and parallelizable just by adapting a few key
paradigms.

Preliminary contents:

  * What is Functional Programming (FP)
  * Relation between the FP and HEP communities
  * FP in C++ and Python for your everyday work
  * FP-inspired techniques in data science (e.g. split-apply-combine or map-reduce)
  * How following FP paradigms enables easy parallelization of your code

Reminder: this will not be a theoretical introduction to FP nor to functional
languages like Haskell or OCaml. It’s a practical talk about how you can profit
from the lessons learned in the FP community to improve your productivity.

## Running the code

### C++ Requirements
  * [ROOT](https://github.com/root-project/root)

### Python requirements
  * [uproot](https://github.com/scikit-hep/uproot)
  * [pandas](https://github.com/pandas-dev/pandas)
  * [numpy](https://github.com/numpy/numpy)
  * [matplotlib](https://github.com/matplotlib/matplotlib)

### Compiling
```
make
```

### Description

* The code `create_data_non_fp.cpp` is the example of filling a TTree the usual way
* The code `create_data_fp.cpp` demonstrates how you can fill a TTree in a
  safer way with the `STree<TreeStructure>` wrapper. Branch types are checkes
  at compile time and no mutable variables are necessary code
* There is `create_data_fp_multithread.cpp`, which aims to demonstrate how
  easiy it is to go to multithreading when your code was written with pure
  functions in mind
* Finally, `make_plot.py` shows how you can do some quick analysis of your
  simulated data using Pandas and the split-apply-combine idiom

### Notes

The multithreading example will not actually speed up the code, because the
"simulation" is to simple that it is bottlenecked by writing to the TTree,
which can't be done in parallel. Think of it as a proof of concept.
