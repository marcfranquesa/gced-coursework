x0 = -2;
x1 = 2;
mx = 500;

y0 = -2;
y1 = 2;
my = 500;

iterations = 100;
scaling_factor = 5;

mandel(x0, x1, mx, y0, y1, my, iterations, scaling_factor)


function mandel(x0, x1, mx, y0, y1, my, iterations, scaling_factor)
    cont = 1;
    cache = [x0, x1, y0, y1];
    prev_C = [];
    prev_V = 0;

    while cont
        last_row = num2cell(cache(end, :));
        [x0, x1, y0, y1] = last_row{:};

        range_x = linspace(x0, x1, mx);
        range_y = linspace(y0, y1, my);
        V = compute_mandel(range_x, range_y, iterations, prev_C, prev_V);
        plot_mandel(x0, x1, y0, y1, V, scaling_factor, iterations, mx, my);

        [cont, iterations, cache, mx, my, scaling_factor] = ...
            user_input(iterations, cache, mx, my, scaling_factor);
    end
end

function [V] = compute_mandel(range_x, range_y, iterations, prev_C, prev_V)
    [CX, CY] = meshgrid(range_x, range_y);
    C = CX + CY*1i;
    
    % only iterations were reduced
    if all(size(prev_C) == size(C)) ...
       && all(prev_C == C) ...
       && (iterations + 1) < max(prev_V, [], 'all')

        V = prev_V;
        B = V > (iterations + 1);
        V(B) = iterations + 1;
        return
    end
    
    Z = zeros(size(C));
    base_B = true(size(C));
    
    % for the motions we do not did to recompute everything
    % so creating a base mask where we use the saved value for the prev_V
    if (iterations + 1) == max(prev_V, [], 'all')
        base_B = ~ismember(C, intersect(C, prev_C));
    end
    V = ones(size(C)) .* (iterations + 1);
    V(~base_B) = prev_V(prev_C, intersect(C, prev_C));
    
    
    for n = 1:iterations
        % update values that have not diverged
        B = base_B & (V == (iterations + 1)) & (abs(Z) <= 2);
        Z(B) = Z(B).^2 + C(B);
        
        % set values values that have diverged
        Bp = base_B & (V == (iterations + 1)) & (abs(Z) > 2);
        V(Bp) = n;
    end
end

function plot_mandel(Xa, Xb, Ya, Yb, V, scaling_factor, iterations, mx, my)
    colormap(brighten(copper, 0));
    image([Xa, Xb], [Ya, Yb], ...
           mod(V * scaling_factor, size(colormap, 1)) + 1);
    title("Mandelbrot fractal")
    axis xy;
    axis equal;
    axis off;
    
    fprintf("\n\n==================================\n")
    fprintf("Mandelbrot fractal at\n")
    fprintf("    X: [%0.9f, %0.9f]\n", Xa, Xb)
    fprintf("    Y: [%0.9f, %0.9f]\n", Ya, Yb)
    fprintf("    Iterations: %18d\n", iterations)
    fprintf("    Scaling factor: %14d\n", scaling_factor)
    fprintf("    Points: %14d  x%5d\n", mx, my)
    fprintf("==================================\n\n")
end

function [cont, iterations, cache, mx, my, scaling_factor] = ...
    user_input(iterations, cache, mx, my, scaling_factor)
    
    cont = 1;

    factor = 1.5;

    [x0, y0, c] = ginput(1);
    if c < 3
        [x1, y1] = ginput(1);
        cache = [cache; x0, x1, y0, y1];
        return
    end

    last_row = num2cell(cache(end, :));
    [x0, x1, y0, y1] = last_row{:};

    extra_y = (y1 - y0) / 5;
    extra_x = (x1 - x0) / 5;
    switch c
        case 'q', 'Q';
            cont = 0;
        case '+'
            iterations = round(iterations * factor);
        case '-'
            iterations = round(iterations / factor);
        case 'u'
            if size(cache, 1) > 1
                cache = cache(1:(end - 1), :);
            end
        case 'X'
            mx = round(mx * factor);
        case 'x'
            mx = round(mx / factor);
        case 'Y'
            my = round(my * factor);
        case 'y'
            my = round(my / factor);
        case 'S'
            scaling_factor = round(scaling_factor * factor);
        case 's'
            scaling_factor = round(scaling_factor / factor);
        
        % some vi motions
        case 'j'
            cache = [cache; x0, x1, y0 - abs(extra_y), y1 - abs(extra_y)];
        case 'k'
            cache = [cache; x0, x1, y0 + abs(extra_y), y1 + abs(extra_y)];
        case 'h'
            cache = [cache; x0 - abs(extra_x), x1 - abs(extra_x), y0, y1];
        case 'l'
            cache = [cache; x0 + abs(extra_x), x1 + abs(extra_x), y0, y1];
        case 32 % case for space, zoom in/out
            [~, ~, b] = ginput(1);
            switch b
                case '+'
                    cache = [cache; x0 + extra_x, x1 - extra_x, ...
                             y0 + extra_y, y1 - extra_y];
                case '-'
                    cache = [cache; x0 - extra_x, x1 + extra_x, ...
                             y0 - extra_y, y1 + extra_y];
            end
        otherwise
            disp(c);
    end
    
end
