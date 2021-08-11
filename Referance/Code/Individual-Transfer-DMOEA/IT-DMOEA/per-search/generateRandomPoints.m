function resPop=generateRandomPoints(Pop)
count=1;
for j=1:size(Pop,2)
    resPop=Pop;
    mutIndex=randperm(ceil(size(Pop,1)*0.5));
    for i=1:mutIndex
        temp=cauchyrnd(Pop(i,j),1);
        if temp <0 || temp>1
           temp =0;
        end
        resPop(i,count)=temp;
        count=count+1;
    end
end
resPop=[resPop Pop];