# SIMULATIONS OF D2D COMMUNICATION IN 5G NB-IOT: PERFORMANCE ANALYSIS OF PATH 
# ATTENUATION, DUTY-CYCLE, AND RETRANSMISSIONS

_IoT aims to provide communication support to an ever-increasing number of devices. Narrowband IoT(NB-IoT) emerged as part of 5G technology focused on sensors and devices deployed almost anywhere. This technology is constantly challenged to improve its coverage, number of connected devices and minimize devices’s battery use. One strategy to extend the NB-IoT’s range is using device-to-device (D2D) communications. Our article presents an analysis of three key parameters in cellular and D2D communications: path attenuation, duty-cycle, and the maximum number of retransmissions. We use 
the expected delivery ratio (EDR) to compare the performance of each configuration using a NB-IoT/D2D integrated simulation tool. The results reveals path-loss exponent and maximum retransmission upper limits in typical urban and suburban scenarios. We expect to shed light on the future designs of NB-IoT infrastructure and its integration with D2D._

<p align="center">
<img aling="center" src="suburban_edr_alpha.pdf" alt="Impact of PLE increment in the EDR and EED with different duty cycles in urban and suburban scenarios" width="250"/>
<img aling="center" src="suburban_qos_medium_d05.pdf" alt="The impact of out-of-coverage UE density and the maximum number of retransmissions on EDR and EED, for suburban scenario" width="250"/>
<img aling="center" src="urban_edr_tau.pdf" alt="Impact of maximum number of retransmissions in the EDR and EED for different duty cycles in urban scenario." width="250"/>
</p>

If you like this simulator, please consider starring [link]( "https://github.com/LICAR-UBA/NBIoT-D2D-Sim") and spreading the word!


# Features

The simulator provides the following features:


- It runs in parallel in your notebook or in a computer cluster, using shared memory.
- Is OpenSource Software! 
   
  
# Installation instructions

To install simulator in GNU/Linux follow the next steps:

1. Install GCC (GNU Compiler Collection), version 7.4.0+
    - Note: to install in Ubuntu 18.04+, type in the console ```sudo apt-get update``` and then ```sudo apt-get install build-essential```
2. Download simulator code from [here](https://github.com/LSC-UBA/OpenEP/archive/master.zip "OpenEP code"), and uncompress the zip file.
3. Download and install Paraview following the instructions in [here](https://www.paraview.org/download/ "Paraview").


# How to setup and run your experiment

1. **D2D-Sim** can be adapted to your specific in-silico experiment by modifiyng the configuration file *parameters.h*. Different illustrative examples can be found in the cases folder.

&nbsp;&nbsp;&nbsp;&nbsp; Aside from regular monopolar pulses, **D2D-Sim** provides the abiliy to simulate .... For this purpose, n parameters must be set:

```c++
  const double a    // dBm
  const double b   // m
```

&nbsp;&nbsp;&nbsp;&nbsp; The ....

&nbsp;&nbsp;&nbsp;&nbsp; To clarify, some examples are sketched below:

   * First example (taken from [...](). ...:

```c++
  const double a    // dBm
  const double b   // m
```

&nbsp;&nbsp;&nbsp;&nbsp; On the other hand, if we want to apply ...:

```c++
  const double a    // dBm
  const double b   // m
```

   * Second example (taken from [...](...)). ....:

```c++
  const double a    // dBm
  const double b   // m
```


   * Third example (taken from [...](...). ....

```c++
  const double a    // dBm
  const double b   // m
```
&nbsp;&nbsp;&nbsp;&nbsp; Apart from treatment parameters, other variables regarding ... can be found in the configuration file *pararameters.h*. For instance:


* Density:
  - **urbans** = 0.007
  - **suburbans** = 0.0007
  
* Foot-prints:
  - **x_max** = 0.032
  - **y_max** = 0.032
  
2. After modifying the configuration file (```src/par.h```), compilation and execution can be done effortlessly typing in the linux terminal: ```./run.sh```. The complete set of options of the bash script are described in the following section. The script will create a directory named ```simulation-1``` with three subdirectories in it: ```bin```, ```data``` and ```src```, which stores the simulation executable file, the output data (Paraview-compliant or csv output files) and the source code of this particular simulation, respectively. Next time the script is executed the simulation directory will be named with the following natural number with regard to the last simulation, i.e. ```simulation-2```.
  
3. In ```simulation-1/data/``` folder you will find vtk and/or csv output files (depending on the selected configuration in ```src/par.h```). Output formats were selected to be compatible with the powerful visualization tool: Paraview. You can find tutorials about Paraview use in [here](https://www.paraview.org/tutorials/ "Paraview Tutorials").
  
  
# More about the software...

## run.sh options

| run.sh option | Description |
|---------------|---------------|
| -d <simulation-directory> | Define the simulation directory. Default: simulation-i, where i is the next number regarding to the previous simulation directory. |
| -n <number-of-threads> | Define the number of threads that will be used by the simulation. Default: number of logical cores of the computer node. |
| -c <compilation-option> | Define the compilation option (see Tab. B.4). Default: FAST OMP. |

| Compilation option | Description |
|---------------|---------------|
| STD | Standard compilation. |
| O3 | Compilation with O3 optimizations. |
| FAST | Compilation with Ofast optimizations. |
| DBG | Compilation with debug mode. |
| OMP | Compilation with OpenMP. |
| O3 OMP | Compilation with O3 optimizations and OpenMP. |
| FAST OMP | Compilation with Ofast optimizations and OpenMP. |

## Code file descriptions

| Source file |  Description  |
|---------------|---------------|
| main.cpp  |  Main simulation process is implemented in this file. | 
| electrics_calc.h, electrics_calc.cpp |  All electric variables (Phi, **E**, sigma, **j**, i, Q) are calculated in these files. Only Phi requires the solution of an equation system. | 
| temp_calc.h, temp_calc.cpp |  Temperature transient solution is solved in these files. | 
| par.h |  Biological, physical and numerical paramenters are declared and/or initialized in this file. | 
| mesh.h, mesh.cpp |   Mesh class keeps information about geometry and domain discretization. Instances of this class are used in the ScalarField class and VectorField class. | 
| scalar_field.h, scalar_field.cpp |   ScalarField class is defined in these files. Instances of this class are used in main.cpp, electrics_calc.h, temp_calc.h for depicting  Phi, |**E**|, |**j**| and sigma. | 
| vector_field.h, vector_field.cpp |   VectorField class is defined in these files. Instances of this class are used in main.cpp, electrics_calc.h and temp_calc.h for depicting **E** and **j**.  | 
| save.h, save.cpp |   Saving of the different scalar and vector fields as well as the log, are implemented in these files.| 


