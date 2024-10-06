function [ P ] = randpoints(varargin)
    % RANDPOINTS - Random points generator
    %   This MATLAB function returns a 2xN matrix of random points
    %   according to the input parameters.
    %
    %   Syntax
    %     P = RANDPOINTS(N)
    %     P = RANDPOINTS(N, distr)
    %     P = RANDPOINTS(N, distr, U, V)
    %
    %   Input Arguments
    %     N - amount of random points
    %       positive integer value
    %     distr - distribution of points
    %       'uniform' (default) | 'uniform'
    %     U - x-axis interval for distribution of points if distr is
    %     'uniform', mean of x, y if distr is 'gaussian'
    %       numeric array of length 2
    %     V - y-axis interval for distribution of points if distr is
    %     'uniform', std of x, y if distr is 'gaussian'
    %       numeric array of length 2
    %

    correct_usage_message = get_correct_usage_message_();

    handle_bad_n_args(varargin{:});
    
    N = varargin{1};

    if ~isnumeric(N) || ~isequal(size(N), [1 1]) || ~(N > 0)
        msg = "\nValue error, amount of random points (N) " + ...
            "has to be an integer strictly larger than 0.\n\n";
        error(sprintf(msg + correct_usage_message));
    end
    
    if nargin == 1
        P = rand(2, N);
        return;
    end

    distr = varargin{2};
    distr_error_msg = "\nValue error, distr can only be 'uniform' or " + ...
        "'gaussian'.\n\n";

    if ~isstring(distr) && ~ischar(distr)
        error(sprintf(distr_error_msg + correct_usage_message));
    end
    
    handle_u_and_v(varargin{:});

    switch distr
        case "uniform"
            P = handle_uniform(varargin{:});
            return;
        case "gaussian"
            P = handle_gaussian(varargin{:});
            return;
        otherwise
            error(sprintf(distr_error_msg + correct_usage_message));
    end
end


function handle_bad_n_args(varargin)
    correct_usage_message = get_correct_usage_message_();

    if nargin == 0
        msg = "\nNot enough args, amount of random points (N) " + ...
                "is required.\n\n";
        error(sprintf(msg + correct_usage_message));
    end

    if nargin == 3
        msg = "\nToo many or not enough args please use 1, 2 or 4 args.\n\n";
        error(sprintf(msg + correct_usage_message));
    end

    if nargin > 4
        msg = "\nToo many args please use 1, 2 or 4 args.\n\n";
        error(sprintf(msg + correct_usage_message));
    end
end


function handle_u_and_v(varargin)
    correct_usage_message = get_correct_usage_message_();
    
    if nargin == 4
        if ~isnumeric(varargin{3}) || ~isequal(size(varargin{3}), [1 2])
            msg = "\nValue error, U has to be a numeric array of length 2.\n\n";
            error(sprintf(msg + correct_usage_message));
        end

        if ~isnumeric(varargin{4}) || ~isequal(size(varargin{4}), [1 2])
            msg = "\nValue error, V has to be a numeric array of length 2.\n\n";
            error(sprintf(msg + correct_usage_message));
        end
    end
end


function [ P ] = handle_uniform(varargin)
    N = varargin{1};
    if nargin == 2
        P = rand(2, N);
        return;
    end

    correct_usage_message = get_correct_usage_message_();

    U = varargin{3};
    A1 = U(1);
    B1 = U(2);
    
    if A1 > B1
        msg = "\nU has to be a valid interval in uniform mode " + ...
            "([a, b] with b >= a).\n\n";
        error(sprintf(msg + correct_usage_message));
    end

    V = varargin{4};
    A2 = V(1);
    B2 = V(2);
    
    if A2 > B2
        msg = "\nV has to be a valid interval in uniform mode " + ...
            "([a, b] with b >= a).\n\n";
        error(sprintf(msg + correct_usage_message));
    end


    P = [ (rand(1, N) * (B1 - A1) + A1); (rand(1, N) * (B2 - A2) + A2) ];
end


function [ P ] = handle_gaussian(varargin)
    N = varargin{1};
    if nargin == 2
        P = randn(2, N);
        return;
    end

    correct_usage_message = get_correct_usage_message_();

    U = varargin{3};
    C1 = U(1);
    C2 = U(2);

    V = varargin{4};
    std1 = V(1);
    std2 = V(2);
    
    if std1 < 0 || std2 < 0
        msg = "\nV has to be a numerical array of valid stds " + ...
            "(non negative real numbers).\n\n";
        error(sprintf(msg + correct_usage_message));
    end

    P = [ (randn(1, N) * std1 + C1); (randn(1, N) * std2 + C2) ];
end


function [ msg ] = get_correct_usage_message_()
    msg = "  Syntax\n" + ...
        "\tP = randpoints(N)\n" + ...
        "\tP = randpoints(N, distr)\n" + ...
        "\tP = randpoints(N, distr, U, V)\n\n";

    msg = msg + ...
        "  Input Arguments\n" + ...
        "\tN - amount of random points\n" + ...
        "\tdistr - distribution of points\n" + ...
        "\t  'uniform' (default) | 'uniform'\n" + ...
        "\tU - x-axis interval for distribution of points if distr is\n" + ...
        "\t'uniform', mean of x, y if distr is 'gaussian' \n" + ...
        "\t  numeric array of length 2\n" + ...
        "\tV - x-axis interval for distribution of points if distr is\n" + ...
        "\t'uniform', std of x, y if distr is 'gaussian' \n" + ...
        "\t  numeric array of length 2\n";
end
