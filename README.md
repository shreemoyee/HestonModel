# HestonModel

Using the Heston Model to price path dependent Asian options

The project is written in C++. The structure of classes is as follows:

-PayOff class
  |
   -- Asian options

-Statistical Distribution
  |
   -- Normal Distribution
    |
     -- Correlated Wiener processes
     
-Path Generation class

-Heston model class

The calculations are being done in a main.cpp that resides in the project root. Eventually I wish to include the following,
1. Use CMake to run the project
2. Create a python client to use the project. 
