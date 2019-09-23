# Noble-Abel Stiffened Gas equation of state calibration

## About :pencil2:
Noble-Abel Stiffened Gas (NASG) equations of state (EOS) calibration for compressible diphasic flow under mechanical equilibrium. 
Calibration of SG EOS parameters is done for a liquid in the presence of its vapor. The EOS parameters are determined from experimental saturation curves.

## Reference :book:
[Le Métayer, O., & Saurel, R. ](https://doi.org/10.1063/1.4945981) (2016).
The noble-abel stiffened-gas equation of state. Physics of Fluids, 28(4), 046102.

## How to use :wrench:

### General remarks

#### 1. Compilation & Run

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
$ make resClean
```

#### 2. General

To run a Noble-Abel Stiffened Gas calibration you must provide two files located at the following path `NASG-EOS_Calibration/input/`:
* `refState.txt` wich contains data of the liquid reference state, the pressure *p<sub>0</sub> (Pa)*, the density *&rho;<sub>0</sub> (kg/m<sup>3</sup>)* and the sound speed *c<sub>0</sub> (m/s)*.
* `expData.txt` which contains experimental saturation data at the temperature range of study. The first line of this file is not read, there are 7 rows to fill (each one separated by a blank or a tab) as follows:

T (K) | Psat (Pa) | vG (m<sup>3</sup>/kg) | vL (m<sup>3</sup>/kg) | hG (J/kg) | hL (J/kg) | Lv (J/kg)
:---: | :---: | :---: | :---: | :---: | :---: |:---:
data | data | data | data | data | data | data

Remark: the decimal separator of *data* must be a dot. 

#### 3. Results and plot

Once the NASG parameters are calibrated you will get their values in the shell environnement.

Theoritical curves can be found in the folder `NASG-EOS_Calibration/res/`. If you want to plot theses curves and compare with the experimental ones you will have to go to the folder `NASG-EOS_Calibration/res/` and run the script `./runPlot.sh`. It might be possible that you don't have the rights to launch this script, thus you will have to do a quick `chmod +x runPlot.sh`

#### 4. Library of test cases 
	
Under the folder `NASG-EOS_Calibration/input/lib/` you can find test cases for validation. The test cases are:
* Liquid/vapor dodecane for temperature range T &isin; [300-500 K].
Experimental data are from [J. R. Simões-Moreira](https://elibrary.ru/item.asp?id=5644923), *“Adiabatic evaporation waves” Ph.D. thesis, Rensselaer Polytechnic Institute, Troy, NY, 1994.*
* Liquid water and steam for temperature range T &isin; [300-500 K].
Experimental data are extracted from [NIST website](https://webbook.nist.gov/chemistry/fluid).
* Liquid/vapor oxygen for temperature range T &isin; [60-100 K].
Experimental data are available at the [NIST website](https://webbook.nist.gov/chemistry/fluid).
