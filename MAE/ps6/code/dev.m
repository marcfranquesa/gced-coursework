N = 100; % length of the symbol sequence
T = 1; % symbol period in seconds
Q = 10; % Oversampling value (integer)
A = 1; % Amplitude
SNR = 10; % Signal to noise ratio in dB
samples = 100 * Q / T; % Length of the pulse vector


N = 100;
T = 2;
Q = 2;
A = 5;

noise_var = 0.5; % already squared
SNR = 10 * log10(A^2 / (T * noise_var));

samples = 100;
Np = 100;


[r, y] = get_signals(N, T, Q, A, SNR, Np, samples);

plot_signal(r, T);
plot_signal(y, T);

