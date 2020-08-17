# Work in Progress: Readme.md

# An Open Source Simulator for the integration of 5G Narrowband Internet of Things and Device-to-Device Communication

_IoT aims to provide communication support to an ever-increasing number of devices. Narrowband IoT (NB-IoT) emerged as part of 5G technology focused on sensors and devices deployed almost anywhere. This technology is constantly challenged to improve its coverage, number of connected devices and minimize devices’s battery use. One strategy to extend the NB-IoT’s range is using device-to-device (D2D) communications. 
We present an open source simulation code for modeling NB-IoT/D2D hybrid communication systems. 
The simulations consider key parameters in cellular and D2D communications, such as D2D interference, transmission power, duty-cycle, device density, path attenuation, and the number of retransmissions. 
Besides, the expected delivery ratio (EDR) and expected end-to-end delay (EED) are used to compare the performance of each study scenario.
The code was developed for a GNU/Linux system. It was written in C, the compilation is assisted by Makefile, and the experiment setup script was written in BASH.
We expect to shed light on the future designs of NB-IoT infrastructure and its integration with D2D._

<p align="center">
<img aling="center" src="suburban_edr_alpha.pdf" alt="Impact of PLE increment in the EDR and EED with different duty cycles in urban and suburban scenarios" width="250"/>
<img aling="center" src="suburban_qos_medium_d05.pdf" alt="The impact of out-of-coverage UE density and the maximum number of retransmissions on EDR and EED, for suburban scenario" width="250"/>
<img aling="center" src="urban_edr_tau.pdf" alt="Impact of maximum number of retransmissions in the EDR and EED for different duty cycles in urban scenario." width="250"/>
</p>

If you like this simulator, please consider starring [link]( "https://github.com/LICAR-UBA/NBIoT-D2D-Sim") and spreading the word!


# Features

The simulator provides the following features:

- It is an in-silico lab, it provides an NB-IoT simulation model integrated with D2D capabilities. 
- It models crucial variables in cellular and D2D communications, including:
    - D2D interference, transmission power, duty dycle, retransmissions, path loss attenuation, user equipment density, footprint radii, packet size and transfer block size,   
- It runs in parallel in your notebook or in a computer cluster, using shared memory.
- Is OpenSource Software! 
   
  
# Installation instructions

To install simulator in GNU/Linux follow the next steps:

1. Install GCC (GNU Compiler Collection), version 7.4.0+
    - Note: to install in Ubuntu 18.04+, type in the console ```sudo apt-get update``` and then ```sudo apt-get install build-essential```
2. Download simulator code from [here](https://github.com/LICAR-UBA/NBIoT-D2D-Sim/archive/master.zip "NBIoT-D2D-Sim code"), and uncompress the zip file.
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
  
  
