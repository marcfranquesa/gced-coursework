transmitters = [1.1 3;1.35 2;4.1 1.5];
distances = [1 1.25 2.5];
colors = ["g", "b", "r"];

main(transmitters, distances, colors)

function main(transmitters, distances, colors)
    validate_input(transmitters, distances, colors)
    
    circle = @(x, y, x0, y0, r) (x - x0) .^ 2 + (y - y0) .^2 - r^2;

    equations = {};
    
    hold on;
    % with a loop we can iterate over all the possible transmitters
    for i=1:size(distances, 2)
        fp = @(x, y) circle(x, y, transmitters(i, 1), transmitters(i, 2), distances(i));
        equations{i} = fp;
        fimplicit(fp, colors(i));
        plot(transmitters(i, 1), transmitters(i, 2), join([colors(i) "."]), "MarkerSize", 15);
    end
    
    % finding and plotting the solution of the first 3 circles
    solution = fsolve(@(X) cellfun(@(f) f(X(1), X(2)), equations(1:3)), [0 0]);
    fprintf("x =\n\t"); disp(solution(1));
    fprintf("y =\n\t"); disp(solution(2));
    plot(solution(1), solution(2), "black.", "MarkerSize", 15); hold on;


    hold off;
    % using the same x/y limits so we get a square
    min_lim = min(transmitters - max(distances), [], "all");
    max_lim = max(transmitters + max(distances), [], "all");
    axis([min_lim max_lim min_lim max_lim]), axis off, axis equal;
end

function validate_input(transmitters, distances, colors)
    if size(transmitters, 2) ~= 2
        error("transmitters should be a Nx2 matrix");
    end

    if size(transmitters, 1) ~= size(distances, 2)
        error("Mismatch between amount of transmitter centers and distances");
    end

    if size(distances, 2) ~= size(colors, 2)
        error("Mismatch between amount of transmitters and colors");
    end

    if size(distances, 2) < 3
        error("At least 3 transmitters needed");
    end
end