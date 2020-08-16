#

# OpenEP: an open source electrical-thermal simulator for electroporation-based treatments

The Internet of Things (IoT) provides communication support to an increasing number of devices. 5G Narrowband-IoT focuses on sensors and devices deployed almost anywhere, constantly evolving to improve coverage, communication quality, and increase the number of devices. Device-to-Device (D2D) establishes a two-hop route, connecting out-of-coverage devices with a base station through a relay. The duty cycle regulates the time a relay employs in D2D mode and can impact on the quality of out-of-coverage communications. No analysis of D2D has been performed considering different environments, channel properties, number of retransmissions and interfering devices. Our article analyzes communication’s performance in two typical scenarios: urban and suburban. We consider the duty cycle, the path-loss exponent, the number of retransmissions and interfering devices, analyzing their impact on the expected delivery ratio, and the end-to-end delay which we use to define QoS zones to reveal the different possible configurations in a determined scenario. Our simulations show the parameter combinations that increase the quality of D2D/NB-IoT communications in urban and suburban scenarios. We hope to shed light on future NB-IoT infrastructure hardware and software design.

<p align="center">
<img aling="center" src="suburban_edr_alpha.pdf" alt="Impact of PLE increment in the EDR and EED with different duty cycles in urban and suburban scenarios" width="250"/>
<img aling="center" src="suburban_qos_medium_d05.pdf" alt="The impact of out-of-coverage UE density and the maximum number of retransmissions on EDR and EED, for suburban scenario" width="250"/>
<img aling="center" src="urban_edr_tau.pdf" alt="Impact of maximum number of retransmissions in the EDR and EED for different duty cycles in urban scenario." width="250"/>
</p>

If you like this simulator, please consider starring [link]( "us on GitHub") and spreading the word!


# Scientific references

This code was explicitly used in the following scientific publications:

- (Under review) "OpenEP: an open source electrical-thermal simulator for electroporation-based treatments". Scientific Reports, Nature. Authors: M. Marino, E. Luján, E. Mocskos, G. Marshall. 2019.
- "Towards an optimal doseresponse relationship in gene electrotransfer protocols". Electrochimica Acta. E. Luján, M. Marino, N. Olaiz, G. Marshall. 2019.

This code implements the standard electroporation model used in scientific publications such as:

- "The Role of Additional Pulses in Electropermeabilization Protocols". Authors: C. Suárez, A. Soba, F. Maglietti, N. Olaiz, G. Marshall. 2014.
- "A Three-Dimensional In Vitro Tumor Platform for Modeling Therapeutic Irreversible Electroporation". Authors: C. B. Arena, C. S. Szot, P. A. Garcia, M. N. Rylander and R. V. Davalos. 2012.
- "Three-dimensional Finite-element Analysis of Joule Heating in Electrochemotherapy and in vivo Gene Electrotransfer". Authors: Igor Lacković, Ratko Magjarević and Damijan Miklavčič. 2009.

# Features

OpenEP provides the following features:

- It is an in-silico lab, allows modeling, planning and optimizing electroporation-based treatments, including
    - Electrochemotherapy (ECT)
    - Irreversible Electroporation (IRE)
    - Gene Electro-Transfer (GET)
- It provides support for variable-pulse protocols, including
    - Combined high-voltage (short), low-voltage (long) pulse regimens.
    - Multiple pulse trains consisting of bursts of the same (amplitude, duration, repetition rate) pulse.
- It models the dynamic of crucial physical variables involved in EP treatments
    - Electric Field, Electric Potential, Electric Current, Electric Conductivity, Current Density, Electric Charge, and Temperature.
- It models two types of electrode geometries
    - Needles, and plates (electrode length, width, thickness, anode-cathode distances, etc.)

- It models three-dimensional domains
- It runs in parallel in your notebook or in a computer cluster, using shared memory.
- Is OpenSource Software! 
   
  
# Installation instructions

To install OpenEP in GNU/Linux follow the next steps:

1. Install GCC (GNU Compiler Collection), version 7.4.0+
    - Note: to install in Ubuntu 18.04+, type in the console ```sudo apt-get update``` and then ```sudo apt-get install build-essential```
2. Download OpenEP code from [here](https://github.com/LSC-UBA/OpenEP/archive/master.zip "OpenEP code"), and uncompress the zip file.
3. Download and install Paraview following the instructions in [here](https://www.paraview.org/download/ "Paraview").


# How to setup and run your experiment

1. **OpenEP** can be adapted to your specific in-silico experiment by modifiyng the configuration file *par.h*. Different illustrative examples can be found in the cases folder.

&nbsp;&nbsp;&nbsp;&nbsp; Aside from regular monopolar pulses, **OpenEP** provides the abiliy to simulate bipolar pulses protocols with variable pulse amplitude and pulse length. For this purpose, five parameters must be set:

```c++
  const double volt_to_dist[]     // V/m
  const double on_pulse_times[]   // s
  const double off_pulse_times[]  // s
  const int pulse_repetitions[]
  const int no_cycles
```

&nbsp;&nbsp;&nbsp;&nbsp; The *i*-th position in *volt_to_dist* array indicates the voltage to distance ratio (in volt per meter) for the *i*-th pulse or *set of pulses*. The *on_pulse_times* and *off_pulse_times* arrays behave in the same way: ON and OFF time duration for the *i*-th pulse or *set of pulses*, respectively. The reason behind the term *set of pulses* is explained by the *pulse_repetitions* array. This array indicates how many pulses have to be applied with the characteristics described in the *i*-th position of the parameters explained above (voltage, ON and OFF). When the last pulse is running (last position in the arrays), the variable *no_cycles* decides whether the simulation has to return to the position 0 of the arrays. If *no_cycles = 1*, the simulation will finish. Otherwise, it will start over.

&nbsp;&nbsp;&nbsp;&nbsp; To clarify, some examples are sketched below:

   * First example (taken from [Zorec 2013](https://www.sciencedirect.com/science/article/pii/S0378517313008557)). The simulation consists of a combination of high voltage and low voltage pulses (HV-LV). The parameters of the HV pulses are: 250000 V/m, 0.0005 sec. ON, and 0.0005 sec. OFF. The parameters of LV pulses are: 22500 V/m, 0.250 sec. ON and 0.1 sec OFF. If we want to apply 3 x HV + 3 x LV (three high-voltage pulses followed by three low-voltage pulses), we must set the five parameters in the following way:

``` c++
  const double volt_to_dist[] = {250000, 22500};  // V/m
  const double on_pulse_times[] = {5e-4, 0.250};  // s
  const double off_pulse_times[] = {5e-4, 0};     // s
  const int pulse_repetitions[] = {3, 3};
  const int no_cycles = 1;
```

&nbsp;&nbsp;&nbsp;&nbsp; On the other hand, if we want to apply (HV + LV) x 3:

``` c++
  const double volt_to_dist[] = {250000, 22500};  // V/m
  const double on_pulse_times[] = {5e-4, 0.250};  // s
  const double off_pulse_times[] = {5e-4, 0.1};   // s
  const int pulse_repetitions[] = {1, 1};
  const int no_cycles = 3;
```

   * Second example (taken from [Sano 2017](https://www.nature.com/articles/srep40747)). We want to simulate 100 burst of symmetric bipolar pulses: 2 *us* of positive pulse (300000 V/m), 1 *us* delay (OFF time) and 2 *us* of negative pulse (- 300000 V/m). The paramaters must be set as follows:

```c++
  const double volt_to_dist[] = {300000, -300000};  // V/m
  const double on_pulse_times[] = {2e-6, 2e-6};     // s
  const double off_pulse_times[] = {1e-6, 1e-6};    // s
  const int pulse_repetitions[] = {1, 1};
  const int no_cycles = 100;
```

   * Third example (taken from [Lackovic 2009](https://ieeexplore.ieee.org/abstract/document/5293947)). In-silico experiment of a monopolar protocol with constant pulse length and pulse amplitude: 8 x 0.250 sec., 25000 V/m at 1 Hz.

```c++
  const double volt_to_dist[] = {25000};      // V/m
  const double on_pulse_times[] = {0.250};    // s
  const double off_pulse_times[] = {0.750};   // s
  const int pulse_repetitions[] = {8};        
  const int no_cycles = 1;
```
&nbsp;&nbsp;&nbsp;&nbsp; Apart from treatment parameters, other variables regarding geometry, electrode shape and tissue characteristics can be found in the configuration file *par.h*. For instance:


* Electrode:
  - **electrode_length** = 0.007
  - **electrode_width** = 0.0007
  - **electrode_thickness** = 0.0007
  - **gap_anode_cathode** = 0.008
  - **electrode_type** = "needles"
  - **gap_elect_elect** = 0.005
  - **no_electrodes** = 1
  
* Domain dimension:
  - **x_max** = 0.032
  - **y_max** = 0.032
  - **z_max** = 0.017
  
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


