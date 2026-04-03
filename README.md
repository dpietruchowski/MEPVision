# MEPVision

MEPVision is a C++ implementation of **Multi Expression Programming (MEP)** applied to binary image processing. The algorithm evolves a population of chromosomes where each chromosome represents a pipeline of image-processing operations (morphological transforms, bitwise logic, thresholding). The fitness of a chromosome is measured by comparing its output image against a reference image using Hamming distance or Hausdorff distance.

## Features

- **Two evolutionary strategies**
  - `GenerationalAlgorithm` – full generational replacement with elitism
  - `SteadyStateAlgorithm` – incremental replacement (individual-by-individual)
- **Gene types**
  - `TerminalGene` – reads the input image
  - `FunctionGene` – applies a pixel-wise operation (bitwise AND/OR/XOR/NOT, absdiff, add, min, max)
  - `MorphoGene` – applies a morphological operation (erode, dilate, open, close, gradient, top-hat, black-hat) with a random structuring element
  - `ThreshGene` – applies binary thresholding
- **Crossover operators** – one-point, two-point, uniform, better-gene
- **Mutation operators** – argument mutation, attribute mutation, combined mutation (random, worst-gene, uniform variants)
- **Fitness functions** – Hamming distance, Hausdorff distance, Hausdorff + Canny, small Hausdorff
- **Parser** – loads a previously saved chromosome from a text file and runs it on a new image

## Dependencies

| Dependency | Minimum version | Notes |
|---|---|---|
| C++ compiler | C++11 | GCC or Clang |
| Qt | 5.x | used for the build system only (qmake) |
| OpenCV | 3.x / 4.x | core, imgproc, highgui, imgcodecs |
| Boost | 1.55+ | boost::range (header-only) and boost_system |

### Ubuntu / Debian

```bash
sudo apt-get install qt5-qmake qtbase5-dev libopencv-dev libboost-system-dev
```

## Building

```bash
mkdir build && cd build
qmake ../MEPVision.pro
make -j$(nproc)
```

The resulting binary is `mep_vision`.

## Usage

### Run the evolutionary algorithm

Edit `main.cpp` to select the algorithm mode and input images, then run:

```bash
./mep_vision
```

By default the program runs the **generational algorithm** (`algorithm()` in `main.cpp`) with:
- Input image: `auto.png`
- Reference image: `auto_ref.png`
- Chromosome size: 100 genes
- Population size: 50 chromosomes
- Iterations: 200

The best chromosome image is saved as `Best <iteration>.png` and the chromosome itself as `Best_<iteration>_<size>.txt`.

### Parse mode – apply a saved chromosome to a new image

Uncomment `parse(argv[1], argv[2])` in `main.cpp` and call:

```bash
./mep_vision <chromosome_file.txt> <input_image.png>
```

The result is saved to `output.png`.

## Project Structure

```
MEPVision/
├── core/           MEP object hierarchy (MEPObject, MEPGene, MEPComposite, MEPChromosome, MEPPopulation)
├── gene/           Concrete gene types (TerminalGene, FunctionGene, MorphoGene, ThreshGene) and their sets
├── fitness/        Fitness functions (Hamming, Hausdorff variants)
├── generator/      Factory classes for creating chromosomes, populations and operations
├── operation/      Crossover and mutation operators
├── selection/      Selection strategies (roulette wheel by fitness/rank, tournament)
├── parser/         File-based chromosome loader
├── main.cpp        Entry point with example algorithm configurations
└── MEPVision.pro   qmake project file
```

## Configuration example

```cpp
GenerationalAlgorithm mep;
mep.selectionType = RANK_ROULETTESELECTION;
mep.setChromosomeSize(100);
mep.setPopulationSize(50);
mep.nIterations = 200;
mep.setInputImage("input.png");
mep.setReferenceImage("reference.png");

// Gene probabilities (must sum to 1)
mep.registerGene(0.1, TERMINALGENE);
mep.registerGene(0.1, FUNCTIONGENE);
double sumPro = mep.registerGene(0.8, MORPHOGENE);
mep.registerGene(1 - sumPro, THRESHGENE);

// Fitness
mep.registerFitness(1, HAMMING);

// Operations (must sum to 1)
mep.registerOperation(0.15, WORST_ARGUMENTMUTATION);
mep.registerOperation(0.15, WORST_ATTRIBUTEMUTATION);
mep.registerOperation(0.20, WORST_COMBINEDMUTATION);
sumPro = mep.registerOperation(0.20, ONEPOINT_CROSSOVER);
mep.registerOperation(1 - sumPro, BETTERGENE_CROSSOVER);

mep.run();
```
