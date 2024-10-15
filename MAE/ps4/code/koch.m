function [ M ] = koch(n)
    % KOCH - Generates the vertices of a Koch fractal
    %   This MATLAB function creates the initial points for a Koch
    %   fractal based on a specified order.
    %
    %   Syntax
    %     KOCH(n)
    %     M = KOCH(n)
    %
    %   Input Arguments
    %     n - order of the Koch fractal
    %       positive integer value
    %
    %   Output
    %     M - generated Koch fractal points
    %       2xN numeric matrix

    origin_x = 0;
    origin_y = 0;
    initial_side_lenth = 1;
    initial_height = origin_y + sqrt(3) * initial_side_lenth / 2;

    M0 = [
        origin_x initial_side_lenth/2+origin_x origin_x+initial_side_lenth origin_x;
        origin_y+initial_height origin_y origin_y+initial_height origin_y+initial_height
    ];
    Patt = get_koch_segment();
    
    if nargout == 0
        genkoch(n, Patt, M0);
    else
        M = genkoch(n, Patt, M0);
    end
end

function [ S ] = get_koch_segment()
    dist = 1;
    side_length = dist / 3;
    height = sqrt(3) * side_length / 2;

    S = [
        0 0.5 - side_length / 2 0.5 0.5 + side_length / 2 1;
        0 0 -height 0 0;
    ];
end