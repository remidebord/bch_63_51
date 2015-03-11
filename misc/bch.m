% BCH[63,51] => m = 6 and k = 51

m = 6;
n = 2^m-1; % Codeword length (total length)
k = 51; % Message length

% Get generator polynomial and error-correction capability.
[genpoly,t] = bchgenpoly(n,k)

% Initialize codeword (63)
codeword = zeros(1, k);

% Initialize message (see C/S T001 - Sample 12-bit BCH Code Calculation)
%message = [1 0 0 1 0 1 0 1 1 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 1 1];
message = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];

% Array size
length = size(message);

% Copy message into codeword (63 - data(26) - bch(12) = 25)
for i = 1:1:length(2)
    codeword(1, 25+i) = message(1, i);
end

% Transform array into galois field GF(2)={0,1}
codeword_gf = gf(codeword)

% Encode bch into codeword
code = bchenc(codeword_gf, n, k)

% Add 2 errors
code(27) = 1;
code(63) = 0;

code

% Decode data
data = bchdec(code, n, k)

