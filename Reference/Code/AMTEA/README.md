# Adaptive Model-based Transfer for Binary problems

This repository contains the Matlab implementation of our work [Curbing Negative Influences Online for Seamless Transfer Evolutionary Optimization](https://www.researchgate.net/publication/326846571_Curbing_Negative_Influences_Online_for_Seamless_Transfer_Evolutionary_Optimization).

## Usage
The `demo.m` file implements a toy example in the paper, in which the source tasks are `one-max` and `one-min`, and the target task is `trap-5`. 

In `MOO\`, we have included examples for AMT-enabled NSGA-II.

In `Knapsack\`, we have included examples for Knapsack problems.

## Citation
> ```
> @ARTICLE{da18tcyb,
>	author={B. Da and A. Gupta and Y. S. Ong},
>	journal={IEEE Transactions on Cybernetics}, 
>	title={Curbing Negative Influences Online for Seamless Transfer Evolutionary Optimization}, 
>	year={2018}, 
>	volume={}, 
>	number={}, 
>	pages={1-14}, 
>	doi={10.1109/TCYB.2018.2864345}, 
>	ISSN={2168-2267}, 
>	month={},
> }
> ```

## Update
Added Python implementation in `./AMETEA_python`.