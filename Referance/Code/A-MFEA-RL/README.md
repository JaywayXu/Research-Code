
# A-MFEA-RL: Adaptive Multi-factorial Evolutionary Optimization for Multi-task Reinforcement Learning
>(ABSTRACT) Evolutionary Computation has largely exhibited its potential to replace conventional learning algorithms in a manifold of Machine Learning tasks, especially those related to unsupervised (clustering) and supervised learning. It has not been until lately when the computational efficiency of evolutionary solvers has been put in prospective for training Reinforcement Learning (RL) models. However, most studies framed in this context so far have considered environments and tasks conceived in isolation, without any exchange of knowledge among related tasks. In this manuscript we present A-MFEA-RL, an adaptive version of the well-known MFEA algorithm whose search and inheritance operators are tailored for multitask RL environments. Specifically, our A-MFEA-RL approach includes crossover and inheritance mechanisms for refining the exchange of genetic material that rely on the multi-layered structure of modern Deep Learning based RL models. In order to assess the performance of the proposed evolutionary multitasking approach, we design an extensive experimental setup comprising different multitask RL environments of varying levels of complexity, comparing them to those furnished by alternative non-evolutionary multitask RL approaches. As concluded from the discussion of the obtained results, A-MFEA-RL not only achieves competitive success rates over the tasks being simultaneously solved, but also fosters the exchange of knowledge among tasks that could be intuitively expected to keep a degree of synergistic relationship.

In the framework, a reformulation of the well-known MFEA/MFEA-II algorithms is introduced. The algorithm is thought so that Multifactorial Optimization can be applied to train neural networks taking advantage of inter-task similarities bi mimicking the traditional **Model-based Transfer Learning** procedure. The adaptation is carried out by means of three crucial points: 

1. **Design of the unified space towards favoring model-based Transfer Learning**: specifically, aspects such as the neural network architecture, the number of neurons of each layer, and the presence of shared layers among models evolved for each task are taken into account.
2. **Adapted crossover operator**: the crossover operator must support the previous aspects by preventing neural models from exchanging irrelevant information.
3. **Layer-based Transfer Learning**: unlike in traditional means to implement Transfer Learning, the number of layers to be transferred between models evolved for different tasks is autonomously decided by A-MFEA-RL during the search. 

The code works on top of [Metaworld-v1](https://github.com/rlworkgroup/metaworld). The experimentation carried out considers three scenarios; *TOY*, *MT-10/MT-10-R* and *MT-50/MT-50-R* (Results included in [Results](#results) Section ), *R* denotes random initialized episodes as in the next image: 

<h3>MT-10-R results
<img src="/uploads/c743460c60cddf1bb099ecae3ea6365d/MT10.gif" width="80%" /> </h3>

# Installation and Experimentation

A-MFEA-RL depends on Metaworld and [MuJoco](https://github.com/openai/mujoco-py) (license required). To automatically install conda environment and Metaworld run ([Mujoco](https://github.com/openai/mujoco-py) is required for this to work):

```bash
chmod +x install.sh
./install.sh
```

The experimentation can be reproduced running:
```bash
python3 exp.py -exp INT -t INT -p STR -r INT
```

* `-exp`: Integer. 0 = TOY, 1 = MT-10/MT-10-R, 2 = MT-50/MT-50-R.
* `-t`: Integer. Number of threads used by Ray.
* `-p`: STRING. Name of the folder under `summary` where results are saved.
* `-r`: Integer. 1 (default) for random reinitialization 0 for fixed reinitialization.

```bash
# Example: Running Fixed MT-10
python3 exp.py -exp 1 -t 8 -p MT-10-F -r 0
# Example: Running Random MT-50
python3 exp.py -exp 2 -t 12 -p MT-50-R
```

# Citing A-MFEA-RL
> Aritz D. Martinez, Javier Del Ser, Eneko Osaba and Francisco Herrera, Adaptive Multi-factorial Evolutionary Optimization for Multi-task Reinforcement Learning, 2020. 