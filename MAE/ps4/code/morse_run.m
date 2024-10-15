P = morse_encoder("I'm here");
PP = [1 0 1 0 0 0 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0 1 0 0 0 1 1 1 0 1 1 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 0 0 1 0 0 0 1 0 1 1 1 0 1 0 0 0 1];
if ~isequal(P, PP)
    error("Mismatch in encoding `I'm here`");
end


pulse_seq = morse_encoder("MAE - SPRING 2024");

tone_freq = 750;
dot_duration = 0.06;
sampling_freq = 8000;

morse_beep(pulse_seq, tone_freq, dot_duration, sampling_freq);j