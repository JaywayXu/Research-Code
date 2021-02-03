% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly executed under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 3275.011166439469434 ; 3279.714133777247753 ];

%-- Principal point:
cc = [ 1525.972527608603741 ; 2014.883021174442547 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.236917409817312 ; -1.050971955025748 ; -0.000209506045764 ; 0.000973058892832 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 10.421031892134764 ; 10.658588249404170 ];

%-- Principal point uncertainty:
cc_error = [ 7.447969691273672 ; 8.965475574003451 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.010488268698602 ; 0.074086801991173 ; 0.001178459991715 ; 0.000989277118001 ; 0.000000000000000 ];

%-- Image size:
nx = 3024;
ny = 4032;


%-- Various other variables (may be ignored if you do not use the Matlab Calibration Toolbox):
%-- Those variables are used to control which intrinsic parameters should be optimized

n_ima = 12;						% Number of calibration images
est_fc = [ 1 ; 1 ];					% Estimation indicator of the two focal variables
est_aspect_ratio = 1;				% Estimation indicator of the aspect ratio fc(2)/fc(1)
center_optim = 1;					% Estimation indicator of the principal point
est_alpha = 0;						% Estimation indicator of the skew coefficient
est_dist = [ 1 ; 1 ; 1 ; 1 ; 0 ];	% Estimation indicator of the distortion coefficients


%-- Extrinsic parameters:
%-- The rotation (omc_kk) and the translation (Tc_kk) vectors for every calibration image and their uncertainties

%-- Image #1:
omc_1 = [ 2.186884e+00 ; 2.053090e+00 ; 1.918919e-02 ];
Tc_1  = [ -3.435134e+02 ; -2.606871e+02 ; 1.372090e+03 ];
omc_error_1 = [ 2.033776e-03 ; 1.824444e-03 ; 4.236066e-03 ];
Tc_error_1  = [ 3.145406e+00 ; 3.783247e+00 ; 4.873227e+00 ];

%-- Image #2:
omc_2 = [ 9.752955e-01 ; 2.449720e+00 ; -7.915514e-01 ];
Tc_2  = [ 1.112516e+02 ; -2.147065e+02 ; 1.858651e+03 ];
omc_error_2 = [ 1.144100e-03 ; 2.674196e-03 ; 3.534233e-03 ];
Tc_error_2  = [ 4.185492e+00 ; 5.081299e+00 ; 5.456041e+00 ];

%-- Image #3:
omc_3 = [ 2.159174e+00 ; 1.119833e+00 ; -5.378165e-02 ];
Tc_3  = [ -4.881520e+02 ; -1.089768e+02 ; 1.832845e+03 ];
omc_error_3 = [ 2.589658e-03 ; 1.576965e-03 ; 3.043897e-03 ];
Tc_error_3  = [ 4.169657e+00 ; 5.051475e+00 ; 6.137228e+00 ];

%-- Image #4:
omc_4 = [ 2.019673e+00 ; 1.805349e+00 ; -2.370529e-01 ];
Tc_4  = [ -2.659440e+02 ; -7.604461e+01 ; 1.858650e+03 ];
omc_error_4 = [ 2.396217e-03 ; 1.982974e-03 ; 3.683604e-03 ];
Tc_error_4  = [ 4.210444e+00 ; 5.072283e+00 ; 5.991259e+00 ];

%-- Image #5:
omc_5 = [ -2.331137e+00 ; -2.004442e+00 ; -5.172273e-01 ];
Tc_5  = [ -4.192247e+02 ; -1.965982e+02 ; 1.687409e+03 ];
omc_error_5 = [ 2.072437e-03 ; 2.198668e-03 ; 4.296566e-03 ];
Tc_error_5  = [ 3.875258e+00 ; 4.691568e+00 ; 6.172236e+00 ];

%-- Image #6:
omc_6 = [ 2.274031e+00 ; 5.627824e-01 ; -1.187377e-01 ];
Tc_6  = [ -3.501601e+02 ; -1.611691e+01 ; 1.972530e+03 ];
omc_error_6 = [ 2.861200e-03 ; 1.419569e-03 ; 2.835909e-03 ];
Tc_error_6  = [ 4.474968e+00 ; 5.397620e+00 ; 6.368354e+00 ];

%-- Image #7:
omc_7 = [ 2.366665e+00 ; 1.614166e+00 ; -1.756281e-01 ];
Tc_7  = [ -2.363962e+02 ; -3.423672e+02 ; 1.866291e+03 ];
omc_error_7 = [ 2.762108e-03 ; 1.913529e-03 ; 3.980899e-03 ];
Tc_error_7  = [ 4.264849e+00 ; 5.081599e+00 ; 6.187305e+00 ];

%-- Image #8:
omc_8 = [ 1.405046e+00 ; 2.284453e+00 ; -2.364100e-03 ];
Tc_8  = [ -2.213227e+02 ; -3.607887e+02 ; 1.958380e+03 ];
omc_error_8 = [ 1.718576e-03 ; 2.327698e-03 ; 3.976551e-03 ];
Tc_error_8  = [ 4.469469e+00 ; 5.351253e+00 ; 6.740512e+00 ];

%-- Image #9:
omc_9 = [ -1.387599e+00 ; -2.663716e+00 ; 7.139888e-02 ];
Tc_9  = [ -5.944581e+01 ; -2.816750e+02 ; 1.969022e+03 ];
omc_error_9 = [ 1.594363e-03 ; 2.955345e-03 ; 5.498936e-03 ];
Tc_error_9  = [ 4.457828e+00 ; 5.387552e+00 ; 6.557443e+00 ];

%-- Image #10:
omc_10 = [ -1.972357e+00 ; -2.351887e+00 ; 4.664994e-02 ];
Tc_10  = [ 1.098348e+02 ; -4.901320e+02 ; 2.018941e+03 ];
omc_error_10 = [ 3.530245e-03 ; 4.387960e-03 ; 6.815957e-03 ];
Tc_error_10  = [ 4.628062e+00 ; 5.510846e+00 ; 7.119303e+00 ];

%-- Image #11:
omc_11 = [ 2.527066e+00 ; 1.807945e+00 ; 2.262962e-01 ];
Tc_11  = [ -3.057945e+02 ; -2.464511e+02 ; 1.714310e+03 ];
omc_error_11 = [ 2.703430e-03 ; 1.772767e-03 ; 4.867279e-03 ];
Tc_error_11  = [ 3.940922e+00 ; 4.722136e+00 ; 5.921694e+00 ];

%-- Image #12:
omc_12 = [ 1.997181e+00 ; 1.633066e+00 ; -4.053278e-01 ];
Tc_12  = [ -3.629707e+02 ; -1.654890e+02 ; 2.146698e+03 ];
omc_error_12 = [ 2.280188e-03 ; 2.145098e-03 ; 3.426699e-03 ];
Tc_error_12  = [ 4.863383e+00 ; 5.881551e+00 ; 6.680579e+00 ];

