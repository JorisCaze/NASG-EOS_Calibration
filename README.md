# Noble-Abel Stiffened Gas equation of state calibration

## About :pencil2:
Noble-Abel Stiffened Gas (NASG) equations of state (EOS) calibration for compressible diphasic flow under mechanical equilibrium. 
Calibration of SG EOS parameters method :
* Liquid and its vapor

## Reference :book:
[Le Métayer, O., & Saurel, R. ](https://doi.org/10.1063/1.4945981) (2016).
The noble-abel stiffened-gas equation of state. Physics of Fluids, 28(4), 046102.

## How to use :wrench:

### General remarks

1. Compilation & Run

	The compilation is done with a Makefile. Under Unix systems it reads :

	```sh
	$ make 
	```

	To run the calibration tool you just need to type the following :
	```sh
	$ ./exe
	```

	If you want to delete all `.o` files from the compilation you can run :
	```sh
	$ make clean
	```

	In case you want to remove the executable `exe`: 
	```sh
	$ make mrproper
	```

	To delete all the result files you can do :
	```sh
	$ make cleanres
	```