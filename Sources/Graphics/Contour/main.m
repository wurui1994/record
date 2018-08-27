clear;clc;
% m=[
%     9 8 3 7 6;
%     8 6 4 2 6;
%     8 1 7 8 4;
%     7 3 5 3 2;
%     8 9 7 6 3;
%     ];
% flag=sign(m-5);
m=peaks';
d=6/49;
mmin=min(min(peaks));
mmax=max(max(peaks));
figure;hold on;x0=-3;y0=-3;
for h=linspace(mmin,mmax,8);
    flag=sign(m-h);
    state(m,flag,d,x0,y0);
end