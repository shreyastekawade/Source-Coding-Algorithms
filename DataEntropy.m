clc;
clear all;
close all;
prompt = 'Enter a string\n';
str=input(prompt,'s');
l=length(str);
uniqchar= unique(str);
lchar=length(uniqchar);
f=zeros(1,lchar);
for i=1:lchar
    f(i)=length(findstr(str,uniqchar(i)));
end
p=zeros(1,lchar);
for i=1:lchar
    p(i)=f(i)/l;
end
Entropy=0;
for i=1:lchar
    Entropy =Entropy + p(i)*log2(1/p(i));
end
Entropy