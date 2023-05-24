clc;
clear all;
close all;

prompt = 'Enter the word : ';
str = input(prompt,'s');
str = (uint8(str))'
%INITIALISE NUMBER OF CODEWORD BITS
n=15;
%INITIALISE NUMBER OF MESSAGE BITS
k = 8;
%%
%INITIALISE ENCODING PROCESS
%INITIALISE PARITY MATRIX = k * n-k = 8 * 7
p = [1 1 1 1 1 1 1;     %1
    1 0 1 1 1 1 1;      %2
    1 1 0 1 1 1 1;      %3
    1 1 1 0 1 1 1;      %4
    1 1 1 1 0 1 1;      %5
    1 1 1 1 1 0 1;      %6
    1 1 1 1 1 1 0;      %7
    1 1 1 1 1 1 1];     %8
%INITIALISE IDENTITY MATRIX
I = eye(k);
%INITIALISE GENERATOR MATRIX
g = [I p] % k by n matrix
%ENLIST CODEWORDS
cw = decimalToBinaryVector(0:2^k - 1); % 2^k by k matrix
%CONVERT THE CODEWORDS & BINARIZE CODEWORDS USING MODULO 2 DIVISION
converted = mod(cw * g,2);
%%
%INITIALISE SYNDROME ERROR CHECKING PROCESS
%CREATE DECODING IDENTITY MATRIX
I2 = eye(n-k);
%CREATE HAMMING PARITY CHECKER MATRIX 
h = [p' I2];

%%
%EXTRACT DATA CHARACTERS FROM CODE LIST
data = zeros(size(str,1),k);
for i=1:1:size(str,1)
    data(i,:) = cw(str(i,1)+1,:);
end
%ENCODE THE CHARACTERS
data
disp(' ');
disp('Time for LBC Encoding: ');
tic
encoded_characters = mod((data * g),2)
toc

encoded = encoded_characters(1,:)';
for i=2:1:size(str,1)
    encoded = [encoded' encoded_characters(i,:)]';
end

%ENCODED MESSAGE = n * 15 BITS
encoded = encoded';

%%SYNDROME VECTORS OF ENCODED CHARACTERS
Syndrome_vectors_of_characters = mod(encoded_characters * h',2)

%%CONVOLUTION ENCODING
data1 = data(1,:)';

for i=2:1:size(data,1)
    data1 = [data1' data(i,:)]';
end
data1 = data1'

p=2;                %number of flip flops used
z=zeros(1,p);
mm=horzcat(data1,z);    %horizontal zeros added with message sequence
d1=0; d2=0;         %initial contents of flip flops
x=[];               %flip flop states
c=[];               %code vector
disp(' ');
disp('Time for Convolution Encoding: ');
tic
for i=1:1:length(mm)
    d1(i+1)= mm(i);
    d2(i+1)= d1(i);
    x=[x; d1(i) d2(i)]; %states of the shift register
    u(i)= xor(x(i,1),x(i,2));
    c1(i)=xor(u(i),mm(i));  %first output bit
    c2(i)=xor(mm(i), x(i,2)); %second output bit
    c=[c c1(i) c2(i)];
end
toc
disp(' ');
disp('Outputs of LBC and Convolution Encoding :')
disp('1. Linear Block Code :')
encoded
disp('2. Convolution Code :')
disp('States of the shift register :')
x
disp('Code vector :')
c
disp('Sizes of LBC and Convolution Outputs :')
sizes = [size(encoded,2) size(c,2)]

file1 = fopen('LBC.txt','w');
file2 = fopen('ConCo.txt','w');
fprintf(file1,'%d',encoded');
fprintf(file2,'%d',c');
