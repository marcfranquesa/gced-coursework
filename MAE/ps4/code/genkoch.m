function [ M ] = genkoch(n, Patt, M0)
    % GENKOCH - Koch fractal generator
    %   This MATLAB function generates a Koch fractal of a given order.
    %
    %   Syntax
    %     GENKOCH(n, Patt, M0)
    %     M = GENKOCH(n, Patt, M0)
    %
    %   Input Arguments
    %     n - order of the Koch fractal
    %       positive integer value
    %     Patt - pattern matrix defining the Koch segment
    %       2xN numeric matrix
    %     M0 - initial set of points for the fractal
    %       2xN numeric matrix
    %
    %   Output
    %     M - generated Koch fractal points
    %       2xN numeric matrix
    %
    
    koch_segment = Patt(:, 2:(end - 1));
    plot_sep = max(M0(2, :)) - min(M0(2, :));
    plot_sep = plot_sep + max(Patt(2, :)) - min(Patt(2, :));
    plot_sep = plot_sep * 1.5;
    M = compute_koch(M0, n, nargout == 0, koch_segment, plot_sep);
end

function [ M ] = compute_koch(M, n, to_plot, koch_segment, plot_sep)
    if to_plot
        plot_koch(M, 1, plot_sep);
        title("Constructing a Koch Fractal of order $n$ = " + string(n), "interpreter", "latex")
        axis equal, axis off;
    end
    k = size(koch_segment, 2);
    
    prev_M = M;
    for i = 2:n
        M = zeros(2, (size(prev_M, 2) - 1) * (k + 1) + 1);
        indices = 1:(k + 1):size(M, 2);
        M(:, indices) = prev_M;

        i0 = indices; i0(end) = [];
        i1 = indices; i1(1) = [];
        
        u0 = M(1, kron(i0, ones(1, k)));
        u1 = M(1, kron(i1, ones(1, k)));
        v0 = M(2, kron(i0, ones(1, k)));
        v1 = M(2, kron(i1, ones(1, k)));
        
        x = kron(ones(size(i0)), koch_segment(1, :));
        y = kron(ones(size(i1)), koch_segment(2, :));
        indices = setdiff(1:size(M, 2), indices);
        M(1, indices) = u0 + (u1 - u0) .* x - (v1 - v0) .* y;
        M(2, indices) = v0 + (v1 - v0) .* x + (u1 - u0) .* y;

        if to_plot
            plot_koch(M, i, plot_sep);
        end

        prev_M = M;
    end
end

function plot_koch(M, n, plot_sep)
    x = M(1, :);
    y = M(2, :) + n * plot_sep;
    plot(x, y, "Color", "blue");
    hold on;
end
