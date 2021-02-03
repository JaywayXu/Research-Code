% Create image pair
Old_Ia = imread('sift_0.jpg') ;
Old_Ib = imread('sift_3.jpg') ;

Ia = single(rgb2gray(Old_Ia)) ;
Ib = single(rgb2gray(Old_Ib)) ;

% Extract features and match
[fa, da] = vl_sift(Ia, 'PeakThresh', 5) ;
[fb, db] = vl_sift(Ib, 'PeakThresh', 5) ;

[matches, scores] = vl_ubcmatch(da, db) ;

[drop, perm] = sort(scores, 'descend') ;
matches = matches(:, perm) ;
scores  = scores(perm) ;

% Show
figure(1) ; clf ;
imagesc(cat(2, Old_Ia, Old_Ib)) ;

xa = fa(1, matches(1, :)) ;
xb = fb(1, matches(2, :)) + size(Ia, 2) ;
ya = fa(2, matches(1, :)) ;
yb = fb(2, matches(2, :)) ;

hold on ;
h = line([xa ; xb], [ya ; yb]) ;
set(h,'linewidth', 1, 'color', 'r') ;

vl_plotframe(fa(:, matches(1, :))) ;
fb(1,:) = fb(1, :) + size(Ia, 2) ;
vl_plotframe(fb(:, matches(2, :))) ;
axis image off ;

saveas(1, 'sift_out', 'jpg') ;