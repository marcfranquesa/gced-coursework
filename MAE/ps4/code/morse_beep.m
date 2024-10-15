function morse_beep(pulse_seq, tone_freq, dot_duration, sampling_freq)
    % MORSE_BEEP - Generates a Morse code beep sound
    %   This MATLAB function produces a Morse code sound based on the
    %   provided pulse sequence, tone frequency, dot duration, and
    %   sampling frequency. It visualizes the resulting Morse signal 
    %   and plays the sound.
    %
    %   Syntax
    %     MORSE_BEEP(pulse_seq, tone_freq, dot_duration, sampling_freq)
    %
    %   Input Arguments
    %     pulse_seq - Sequence of pulses representing Morse code
    %       binary array (1 for dot/dash, 0 for space)
    %     tone_freq - Frequency of the tone for the beep sound
    %       scalar value in Hz
    %     dot_duration - Duration of a dot in seconds
    %       scalar value
    %     sampling_freq - Sampling frequency for the sound
    %       scalar value in Hz

    samples_per_dot = round(dot_duration * sampling_freq);
    
    t_dot = (0:samples_per_dot-1) / sampling_freq;
    
    dot_sound = cos(2 * pi * tone_freq * t_dot);
    
    morse_signal = kron(pulse_seq, dot_sound);

    plot(1:size(morse_signal, 2), morse_signal);
    title("Morse Signal");
    xlabel("Index");
    grid on;
    
    sound(morse_signal, sampling_freq);
end