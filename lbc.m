clc;
clear all;
close all;

prompt = 'Enter the word : ';
str = input(prompt,'s');
str = (uint8(str))';
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
G = [I p]; % k by n matrix
%ENLIST CODEWORDS
cw = decimalToBinaryVector(0:2^k - 1); % 2^k by k matrix
%CONVERT THE CODEWORDS & BINARIZE CODEWORDS USING MODULO 2 DIVISION
converted = mod(cw * G,2);
%%
%INITIALISE SYNDROME ERROR CHECKING PROCESS
%CREATE DECODING IDENTITY MATRIX
I2 = eye(n-k);
%CREATE HAMMING PARITY CHECKER MATRIX 
h = [I2 p'];

%%
%EXTRACT DATA CHARACTERS FROM CODE LIST
data = zeros(size(str,1),k);
for i=1:1:size(str,1)
    data(i,:) = cw(str(i,1)+1,:);
end
%ENCODE THE CHARACTERS
encoded_characters = mod((data * G),2)

encoded = encoded_characters(1,:)';
for i=2:1:size(str,1)
    encoded = [encoded' encoded_characters(i,:)]';
end
%ENCODED MESSAGE = n * 15 BITS
encoded = encoded'
size(encoded);
%%SYNDROME VECTORS OF ENCODED CHARACTERS
Syndrome_vectors_of_characters = mod(encoded_characters * h',2)
