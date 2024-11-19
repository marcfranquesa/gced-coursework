function [r, y] = get_signals(N, T, Q, A, SNR, Np, idxs)
    %GET_SIGNALS Generate PAM signal and its filtered version.
    %   [R, Y] = GET_SIGNALS(N, T, Q, A, SNR, Np, IDXS) generates a noisy
    %   modulated signal R and its filtered version Y based on the input
    %   parameters.
    %
    %   Inputs:
    %       N    - Number of symbols.
    %       T    - Symbol duration.
    %       Q    - Number of samples per symbol.
    %       A    - Signal amplitude.
    %       SNR  - Signal-to-noise ratio in dB.
    %       Np   - Length of the filter for post-processing.
    %       IDXS - (Optional) Indices of the signal to sample. Defaults
    %              to 1:(N * Q) if not provided or is scalar.
    %
    %   Outputs:
    %       R - The modulated noisy signal.
    %       Y - The filtered version of R.
    
    if nargin < 6
        idxs = 1:(N * Q);
    elseif isscalar(idxs)
        idxs = 1:idxs;
    end
    
    n_samples = numel(idxs);
    
    b = (randi([0, 1], 1, N) * 2 - 1) * A;
    
    % Rectangular modulation pulse
    rect_idxs = (idxs - (0:(N - 1))' * Q);
    rect_mod_pulse = get_rectangular_modulation_pulse(T, Q, rect_idxs);
    
    % Generating the noise
    noise_var = A ^ 2 / (10 ^ (SNR / 10)) / T; % Inverting the SNR
    w = sqrt(noise_var) * randn(1, n_samples);
    
    r = b * rect_mod_pulse + w;
    
    p = ones(1, Np);
    y = conv(r, p);
end

function pulse = get_rectangular_modulation_pulse(T, Q, idxs)
    %GET_RECTANGULAR_MODULATION_PULSE Generate a rectangular modulation pulse.
    %   PULSE = GET_RECTANGULAR_MODULATION_PULSE(T, Q, IDXS) generates a
    %   sampled rectangular pulse based on the input parameters.
    %
    %   Inputs:
    %       T    - Symbol duration.
    %       Q    - Number of samples per symbol.
    %       IDXS - Indices of the samples.
    %
    %   Outputs:
    %       PULSE - The sampled rectangular modulation pulse.
    
    t = idxs * T / Q; % Sampled pulse
    pulse = 1 / sqrt(T) * rectpuls((t - T / 2) / T, 1);
end
