A minimal example of C++ code organisation using a logistic differential equation model, solved using numerical (Runge Kutta 4th order) integration. Allows also for parameter estimation using a simple approximate Bayesian computation rejection sampler algorithm (see ```src/ABC_rejection.cpp``` for full implementation). 

To build:

```
make
./logistic
```

When prompted, the user can choose to simulate data from the model (type ```0```) or estimate the parameters (type ```1```). If estimating parameters, a data file called ```data.txt``` with no headers or rownames needs to placed into ```data/```. The data needs to contain only the population size at each time point. The parameter estimates will be stored as ```outputs/estimates.txt```. 

To clean: 

```
make clean
```


