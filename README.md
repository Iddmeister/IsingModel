# Assessment 2 - Ising Model

This 


## Compilation and Execution

The C++ source code in main was compiled using a makefile
```
make
```
to generate a executable called 'main', this was then run with the command
```
./main
```
Optional command line parameters can also be passed to the program
```
./main num_atoms num_configurations iterations J seed output_directory
```
num_atoms is the length of the grid of atoms
num_configurations is the number of configurations to simulate
iterations is the number of iterations to run the simulations for each configuration
J is a scalar
seed is a random number seed to generate different results
output_directory is the directory to output the resulst to

a list of temperatures can also be appended to the arguments to be simulated

e.g.

```
./main num_atoms num_configurations iterations J seed output_directory temp1 temp2 temp3 ...
```


## Navigating the repository

The available branches can be viewed with
```
git branch
```
which will display the branches shown below
```
1D-configuration-determination
1D-iteration-determination
1D-model
1D-multiple-configs
2D-iteration-determination
2D-multiple-configs
main
```

You may switch between branches with
```
git checkout new_branch
```
An entire log of all changes to the current branch can be viewed with
```
git log
```
You may also switch to a specific tag using
```
git checkout tag_name
```
