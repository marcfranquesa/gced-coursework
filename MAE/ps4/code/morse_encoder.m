function [ P ] = morse_encoder(message)
    % MORSE_ENCODER - Encodes a message into Morse code
    %   This MATLAB function converts a given message into Morse code 
    %   representation and can return the Morse code in binary 
    %   format.
    %
    %   Syntax
    %     MORSE_ENCODER(message)
    %     P = MORSE_ENCODER(message)
    %
    %   Input Arguments
    %     message - Input string to be converted into Morse code
    %
    %   Output
    %     P - Morse code representation of the input message
    %       binary array
    [ alpha, morse, total_chars ] = get_data();

    translator = dictionary(alpha(:), (1:total_chars)');

    P = get_morse_message(message, translator, morse);

    if nargout > 0
        P = get_morse_binary(P);
        return
    end

    disp(P);
end

function [ alpha, morse, total_chars ] = get_data()
    data = load("morse.mat");

    alpha = char(data.Alpha + " ");
    total_chars = size(alpha, 2);

    morse = data.Morse;
    morse(total_chars) = {' '};
end

function [ P ] = get_morse_message(message, translator, morse)
    message = char(upper(message));
    length_message = length(message);

    get_morse = @(index)(morse(translator(message(index))));
    
    output = "";

    if length_message > 0
        output = output + get_morse(1);
    end

    for i = 2:length_message
        output = output + " " + get_morse(i);
    end

    P = output;
end

function [ P ] = get_morse_binary(message)
    P = [];
    message = char(message);
    for i = 1:length(message)
        current_char = message(i);
        switch current_char
            case "."
                binary = 1;
            case "-"
                binary = [1 1 1];
            case " "
                binary = [0];
            otherwise
                disp(current_char);
        end
        P = [P binary 0];
    end
    if i > 1
        P(end) = [];
    end
end