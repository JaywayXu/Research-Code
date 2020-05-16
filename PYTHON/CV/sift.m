Ia = imread('part1.jpg');
%vl_impattern('roofs1') ;
Ia = single(rgb2gray(Ia)) ;
Ib = imread('part2.jpg');
%Ib = vl_impattern('roofs2');
Ib = single(rgb2gray(Ib)) ;
[fa, da] = vl_sift(Ia,'PeakThresh', 17) ;
[fb, db] = vl_sift(Ib,'PeakThresh', 17) ;
[matches, scores] = vl_ubcmatch(da, db) ;
[drop, perm] = sort(scores, 'descend') ;%%降序排列两个点的欧式距离，perm是索引，drop是降序结果，drop=scores（perm）
matches = matches(:, perm) ;            %%得到排序后？？
scores  = scores(perm) ;                %%降序后的欧式距离

figure(1) ; clf ;
imagesc(cat(2, Ia, Ib)) ;
axis image off ;
%vl_demo_print('sift_match_1', 1) ;

figure(2) ; clf ;
imagesc(cat(2, Ia, Ib)) ;

xa = fa(1,matches(1,:)) ;%%each fa is a feature frame and has the format [x;y;s;th],where x,y is the center of the frame,s is the scale 
xb = fb(1,matches(2,:)) + size(Ia,2) ;
ya = fa(2,matches(1,:)) ;
yb = fb(2,matches(2,:)) ;

hold on ;
h = line([xa ; xb], [ya ; yb]) ;
set(h,'linewidth', 0.01, 'color', 'r') ;

vl_plotframe(fa(:,matches(1,:))) ;
fb(1,:) = fb(1,:) + size(Ia,2) ;
vl_plotframe(fb(:,matches(2,:))) ;
axis image off ;

vl_demo_print('sift_match_2', 1) ;
