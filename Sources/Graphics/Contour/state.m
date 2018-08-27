function state(m,flag,d,x0,y0)
hold on;%axis([1 5 1 5]);grid on;
%set(gca,'xtick',1:5,'ytick',1:5);
x=[];y=[];
for i=1:size(m,1)-1
    for j=1:size(m,2)-1
        %
        if flag(i,j)<0&&flag(i+1,j)<0&&flag(i,j+1)<0&&flag(i+1,j+1)<0 %0000
            %none
        elseif flag(i,j)>=0&&flag(i+1,j)<0&&flag(i,j+1)<0&&flag(i+1,j+1)<0 %1000
            x=[i+0.5 i];y=[j j+0.5];
        elseif flag(i,j)<0&&flag(i+1,j)<0&&flag(i,j+1)>=0&&flag(i+1,j+1)<0 %0010
            x=[i i+0.5];y=[j+0.5 j+1];
        elseif flag(i,j)<0&&flag(i+1,j)<0&&flag(i,j+1)<0&&flag(i+1,j+1)>=0 %0001
            x=[i+0.5 i+1];y=[j+1 j+0.5];
        elseif flag(i,j)<0&&flag(i+1,j)>=0&&flag(i,j+1)<0&&flag(i+1,j+1)<0 %0100
            x=[i+0.5 i+1];y=[j j+0.5];
        elseif flag(i,j)>=0&&flag(i+1,j)<0&&flag(i,j+1)>=0&&flag(i+1,j+1)<0 %1010
            x=[i+0.5 i+0.5];y=[j j+1];
        elseif flag(i,j)>=0&&flag(i+1,j)>=0&&flag(i,j+1)<0&&flag(i+1,j+1)<0 %1100
            x=[i i+1];y=[j+0.5 j+0.5];
        elseif flag(i,j)>=0&&flag(i+1,j)<0&&flag(i,j+1)<0&&flag(i+1,j+1)>=0 %1001
            x=[i+0.5 i+1 i i+0.5];y=[j j+0.5 j+0.5 j+1];
        elseif flag(i,j)>=0&&flag(i+1,j)>=0&&flag(i,j+1)>=0&&flag(i+1,j+1)>=0 %1111
            %none
        elseif flag(i,j)<0&&flag(i+1,j)>=0&&flag(i,j+1)>=0&&flag(i+1,j+1)>=0 %0111
            x=[i i+0.5];y=[j+0.5 j];
        elseif flag(i,j)>=0&&flag(i+1,j)>=0&&flag(i,j+1)<0&&flag(i+1,j+1)>=0 %1101
            x=[i i+0.5];y=[j+0.5 j+1];
        elseif flag(i,j)>=0&&flag(i+1,j)>=0&&flag(i,j+1)>=0&&flag(i+1,j+1)<0 %1110
            x=[i+0.5 i+1];y=[j+1 j+0.5];
        elseif flag(i,j)>=0&&flag(i+1,j)<0&&flag(i,j+1)>=0&&flag(i+1,j+1)>=0 %1011
            x=[i+0.5 i+1];y=[j j+0.5];
        elseif flag(i,j)<0&&flag(i+1,j)>=0&&flag(i,j+1)<0&&flag(i+1,j+1)>=0 %0101
            x=[i+0.5 i+0.5];y=[j j+1];
        elseif flag(i,j)<0&&flag(i+1,j)<0&&flag(i,j+1)>=0&&flag(i+1,j+1)>=0 %0011
            x=[i i+1];y=[j+0.5 j+0.5];
        elseif flag(i,j)<0&&flag(i+1,j)>=0&&flag(i,j+1)>=0&&flag(i+1,j+1)<0 %0110
            x=[i+0.5 i+1 i i+0.5];y=[j+1 j+0.5 j+0.5 j];
        end
        if length(x)==2
            line(x0+x*d,x0+y*d);
        elseif length(x)==4
            line(x0+x(1:2)*d,x0+y(1:2)*d);
            line(x0+x(3:4)*d,x0+y(3:4)*d);
        end
        %
    end
end