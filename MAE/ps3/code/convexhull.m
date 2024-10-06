function [ H ] = convexhull(P)
    % CONVEXHULL - convex hull finder
    %   This MATLAB function returns a set of indices corresponding to the
    %   convex hull of the input (a set of points).
    %
    %   Syntax
    %     H = CONVEXHULL(P)
    %
    %   Input Arguments
    %     P - random points
    %       a matrix of size 2xN containing real numbers representing
    %       unique points on the plane, at least 3 points required
    %
    correct_usage_message = get_correct_usage_message_();
    
    if nargin ~= 1
        msg = "\nFunction can only be used with 1 input (P).\n\n";
        error(sprintf(msg + correct_usage_message));
    end

    if ~isnumeric(P) ...
        || ~isequal(size(P, 1), 2) ...
        || ~isequal(ndims(P), 2) ...
        || size(P, 2) < 3 ...
        || ~isequal(size(unique(P', "rows"), 1), size(P, 2))
        msg = "\nValue error, points matrix (P) " + ...
            "has to be of size 2xN and contain at least 3 unique " + ...
            "pairs of real numbers.\n\n";
        error(sprintf(msg + correct_usage_message));
    end

    H = compute_convexhull(P);
    
    % plot results
    % plot(P(1, :), P(2, :), 'o');
    % hold on;
    % plot(P(1, H), P(2, H), "b");
end

function [ H ] = compute_convexhull(P)
    X = P(1, :);
    Y = P(2, :);
    
    % initialising the algorithm
    i = get_first_point(X, Y);
    ref_angle = pi / 2;
    H = i;

    while (size(H, 2) == 1) | ~isequal(H(1), H(end))
        p_prev = P(:, H(end));
    
        Xp = X - p_prev(1);
        Yp = Y - p_prev(2);
    
        angles = atan2(Yp, Xp) - ref_angle;
        n_angles = mod(angles, 2*pi);
        
        % setting the current point to max angle to not repeat
        n_angles(i) = 2 * pi;

        min_angle = min(n_angles);
        ref_angle = ref_angle + min_angle;
    
        i_min = find(n_angles == min_angle);
        
        % ordering in H by distance to current pointb
        D2 = (X(i_min) - p_prev(1)) .^ 2 + (Y(i_min) - p_prev(2)) .^ 2;
        [~, perm] = sort(D2);
        i = i_min(perm);
    
        H = [H i];
    end

end

function [ i ] = get_first_point(X, Y)
    i_candidates = find(X == max(X));
    [~, j] = max(Y(i_candidates));
    i = i_candidates(j);
end

function [ msg ] = get_correct_usage_message_()
    msg = "  Syntax\n" + ...
        "\tH = convexhull(P)\n";

    msg = msg + ...
        "  Input Arguments\n" + ...
        "\tP - random points\n" + ...
        "\tdistr - distribution of points\n" + ...
        "\t  a matrix of size 2xN containing real numbers representing " + ...
        "unique points on the plane, at least 3 points required";
end