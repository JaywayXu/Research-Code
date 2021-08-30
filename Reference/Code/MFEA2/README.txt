This particular demo contains the source codes for the multitasking algorithms, namely, MFEA-II and  MFEA-I.  
Further, the source codes for the  single tasking  algorithm, CEA is also provided.  
--------------------------------------------------------------------------------------------------

%% MFEA-II

The implementation of MFEA-II algorithm is provided in the “MFEA2.m” file.  Herein, the rmp values 
(contained in a symmetric RMP matrix) are learned online throughout the multitasking search.  
It is based on the following reference: 

Bali, K. K., Ong, Y. S., Gupta, A., & Tan, P. S. “Multifactorial Evolutionary Algorithm with Online 
Transfer Parameter Estimation: MFEA-II”. IEEE Transactions on Evolutionary Computation, 2019.

The “MAIN.m” file provides a sample demo for the MFEA-II.  Simple toy problems are used as examples.  
-----------------------------------------------------------------------------------------------------

%% MFEA-I

This MFEA-I is an improved version of the existing  MFEA algorithm initially proposed in: 
   
Gupta, A., Ong, Y. S., & Feng, L. (2016). “Multifactorial evolution: toward evolutionary multitasking”.  
IEEE Transactions on Evolutionary Computation, 20(3), 343-357.
 
Herein, the rmp = 0.3, which remains fixed throughout the optimization phase.  
------------------------------------------------------------------------------------------------------

%% CEA 

The “CEA.m” file is an implementation of the single tasking algorithm (CEA). 
Herein, the rmp = 0, implying no knowledge transfers across different tasks.  
  
 