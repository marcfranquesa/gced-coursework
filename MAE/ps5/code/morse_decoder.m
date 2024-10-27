dot_duration = 0.06;
tone_frequency = 750;
sampling_frequency = 8000;
file = "morse_audio_signal.wav";
samples_to_plot = 4000;

expected_tone_frequency = 750;
fir_filter_coef = 64;


main( ...
    file, ...
    dot_duration, ...
    tone_frequency, ...
    sampling_frequency, ...
    samples_to_plot, ...
    expected_tone_frequency, ...
    fir_filter_coef ...
)

function main( ...
    file, ...
    dot_duration, ...
    tone_frequency, ...
    sampling_frequency, ...
    samples_to_plot, ...
    expected_tone_frequency, ...
    fir_filter_coef ...
)
    % part 1
    y = validate_input( ...
        file, ...
        dot_duration, ...
        tone_frequency, ...
        sampling_frequency, ...
        samples_to_plot, ...
        expected_tone_frequency, ...
        fir_filter_coef ...
    );
    
    % part 2
    sound(y);
    figure, plot(y(1:samples_to_plot));

    idx = round(linspace(1, size(y, 1), samples_to_plot));
    figure, plot(y(idx));

    % part 3
    get_psd(y, sampling_frequency, expected_tone_frequency);

    % part 4
    base_band_signal = get_base_band_signal( ...
        y, ...
        fir_filter_coef, ...
        expected_tone_frequency, ...
        sampling_frequency, ...
        dot_duration ...
    );
    % part 5
    ds = get_derivative(base_band_signal);

    % part 6
    decode(base_band_signal, ds, sampling_frequency, dot_duration);
end

function [ y ] = validate_input( ...
    file, ...
    dot_duration, ...
    tone_frequency, ...
    sampling_frequency, ...
    samples_to_plot, ...
    expected_tone_frequency, ...
    fir_filter_coef ...
)
    if ~isfile(file)
        error("File used does not exist.")
    end

    [y, Fs] = audioread(file);
    
    if Fs ~= sampling_frequency
        error("Given frequency does not match with the frequency found in the .wav file.")
    end
end

function get_psd(y, sampling_frequency, expected_tone_frequency)
    [psd, freq] = periodogram(y, [], [], sampling_frequency); 
    [~, max_idx] = max(psd);
    peak_frequency = freq(max_idx);

    fprintf("Tone Frequency: %.2f Hz\n", peak_frequency);
    figure, plot(freq, 10*log10(psd)); % decibel scale
    xlabel("Frequency (Hz)");
    ylabel("Power/Frequency (dB/Hz)");
    title("Power Spectral Density Estimate (Periodogram)");

    if abs(peak_frequency - expected_tone_frequency) > 10
        error("Tone frequency found is not close to the one expected.")
    end
end

function [ base_band_signal ] = get_base_band_signal( ...
        y, ...
        fir_filter_coef, ...
        expected_tone_frequency, ...
        sampling_frequency, ...
        dot_duration ...
    )
    duration = size(y, 1) / sampling_frequency;
    
    t = round(duration * linspace(0, 1, size(y, 1)), 3);

    sine_wave = sin(2 * pi * expected_tone_frequency * t);
    base_band_signal = y' .* sine_wave;
 
    cutoff = sampling_frequency / 2;
    bandwidth = 5 / (cutoff * dot_duration);

    fir_filter = fir1(fir_filter_coef, bandwidth);
    base_band_signal = filter(fir_filter, 1, base_band_signal);
    
    figure, stairs(base_band_signal);
end

function [ ds ] = get_derivative(signal)
    ds = diff(signal);
    figure, plot(ds);
    title("Approximate derivative");
end

function decode(signal, ds, sampling_frequency, dot_duration)

    % smooth out the function
    ds = smoothdata(ds, 'movmean', 5);
    ds(abs(ds) < max(ds) * 0.9) = 0;
    
    % find maximums
    maxes = islocalmax(ds);
    idxs = find(maxes);
    idxs = [ 0 idxs ];
    
    % finding dots until max
    time_to_max = diff(idxs) / sampling_frequency;
    dots_to_max = round(time_to_max / dot_duration);
    
    % keeping only those relevant
    dots_to_max(dots_to_max == 0) = [];
    
    % convert to morse code `.`/`-`/` `
    morse = "";
    for i = 1:length(dots_to_max)
        to_add = "";
        if mod(i, 2) == 1
            switch dots_to_max(i)
                case 1
                    to_add = ".";
                case 3
                    to_add = "-";
                otherwise
                    disp("ISSUE");
            end
        else
            switch dots_to_max(i)
                case 1 % different symbol
                    continue;
                case 3 % different char
                    to_add = " ";
                case 7 % different word
                    to_add = "   ";
                otherwise
                    disp("ISSUE");
            end
        end

        morse = morse + to_add;
    end
    
    disp(morse);
    morse_words = strsplit(morse, "   ");
    
    % building morse to char dict
    morse_data = load("morse.mat");
    dict = containers.Map();
    for i = 1:length(morse_data.Alpha)
        key = string(morse_data.Morse{i});
        value = morse_data.Alpha(i);
        dict(key) = value;
    end

    % convert morse code `.`/`-`/` ` to actual text
    text = "";
    for i=1:length(morse_words)
        morse_chars = strsplit(morse_words(i), " ");
        for j=1:length(morse_chars)
            text = text + dict(morse_chars(j));
        end

        text = text + " ";
    end

    disp(text);
end