# SIMULATIONS OF D2D COMMUNICATION IN 5G NB-IOT: PERFORMANCE ANALYSIS OF PATH 
# ATTENUATION, DUTY-CYCLE, AND RETRANSMISSIONS

_Internet of Things (IoT) aims to provide communication support to an 
ever-increasing number of devices. Narrowband IoT(NB-IoT) emerged as part 
of 5G technology focused on sensors and devices deployed almost anywhere.
This technology is constantly challenged to improve its coverage, number of 
connected devices and minimize devices’s battery use. One strategy to extend 
the NB-IoT’s range is using device-to-device (D2D) communications. Our article 
presents an analysis of three key parameters in cellular and D2D communications:
path attenuation, duty-cycle, and the maximum number of retransmissions. We use 
the expected delivery ratio (EDR) to compare the performance of each 
configuration using a NB-IoT/D2D integrated simulation tool. The results reveals
path-loss exponent and maximum retransmission upper limits in typical urban and 
suburban scenarios. We expect to shed light on the future designs of NB-IoT 
infrastructure and its integration with D2D._

## Starting 

_These instructions will allow you to obtain a copy of the running project 
on your local machine for development and testing purposes._

_See ** Deployment ** to learn how to deploy the project._


### Requirements

_C++_

_Python3_

_Mathplotlib_


### Instalation

_In the root folder, you can run all simulations using:_


_$./run.sh_


_If you want to change the simulation's parameters, you must to edit 
parameters.h file, in the src folder.


## Running the tests 

# The run.sh script compiles and runs the simulation.
# How to use it: 
# run.sh -d <simulation-directory> -c <compilation-type> 

_After executing the run.sh file, in the simulations folder, you will find_
_the results of the simulations made both in csv format and the generated graphics_

### End-to-end testing analysis

In this work we analyze, through an NB-IoT/D2D integrated simulation model, 
the impact on the EDR of three important wireless communication parameters: 
path-loss or path attenuation, duty-cycle, and the maximum number of 
retransmissions. The figures show the behavior of the EDR in the urban and 
suburban scenarios regarding the path-loss exponent for different duty-cycles. 

## Built with

* [ANSI C language](https://gcc.gnu.org/) - Model language
* [Python3](https://www.python.org/) - Graphics language
* [Mathplotlib](https://matplotlib.org/) - Graphics library

## Authors ✒️

* **Emmanuel Luján** - *Original and actual work* - 
[elujan](https://github.com/elujan)
* **Rodolfo Leonardo Sumoza Matos** - *Original and actual work* - 
[rsumoza](https://github.com/rsumoza)
* **Estaban Eduado Mocskos** - *Technical assesment* - 
[emocskos](https://github.com/emocskos)


## Licence

GNU GPL v2.

## ACKNOWLEDGMENTS

The authors would like to thank Consejo Nacional de Investigaciones Cientı́ficas 
y Técnicas (CONICET) and Universidad de Buenos Aires (UBA), Argentina. 
R. L. Sumoza Matos and E. Luján have doctoral and post-doctoral fellowships 
from CONICET and UBA, respectively. E. E. Mocskos is a researcher at
CONICET.



