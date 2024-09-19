% tetris([1,6,0,1;2,5,1,1;4,7,0,0;3,7,8,2;2,5,7,3;5,10,3,1;5,3,9,3;2,8,15,1;7,5,3,1;6,11,0,1;5,1,0,0;3,9,2,1]);
function [] = tetris(pieces)
    % GRID CONSTANTS
    HORIZONTAL_SQUARES = 12;
    VERTICAL_SQUARES = 20;
    GRID_BORDER_WIDTH = 5;
    PIECE_BORDER_WIDTH = 2;
    
    % COLORS
    LIGHT_GRAY = 0.9 * ones(1, 3);
    DARK_GRAY = 0.7 * ones(1, 3);
    
    [X_grid, Y_grid] = get_grid_coordinates(HORIZONTAL_SQUARES, VERTICAL_SQUARES);
    draw_grid(X_grid, Y_grid, LIGHT_GRAY, DARK_GRAY, GRID_BORDER_WIDTH)

    [X_pieces, Y_pieces, colors] = get_pieces();
    draw_piece = @(piece)(draw_piece_aux(piece(1), piece(2), piece(3), piece(4), X_pieces, Y_pieces, colors, PIECE_BORDER_WIDTH));
    
    draw_pieces(pieces, draw_piece);
end

function [X, Y] = get_grid_coordinates(horizontal_squares, vertical_squares)
    foo = @(t)([t t t+1 t+1]);
    Xb = cell2mat(arrayfun(foo, 0:(horizontal_squares - 1), "UniformOutput", false))';
    X = repmat(Xb, 1, vertical_squares);

    bar = @(t)([t t+1 t+1 t]);
    Yb = cell2mat(arrayfun(bar, 0:(vertical_squares - 1), "UniformOutput", false)')';
    Y = repmat(Yb, horizontal_squares, 1);
end

function [] = draw_grid(X, Y, background_color, border_color, border_width)
    fill(X, Y, background_color, "LineWidth", border_width, "EdgeColor", border_color);
    set(gca,'color','none')
    axis([0 size(Y, 2) 0 size(X, 2)]), axis equal, axis off;
end

function [X, Y, colors] = get_pieces()
    X = {};
    Y = {};
    colors = {};
    C = 0.025;

    % PIECE 1
    X{1} = [0+C 0+C 4-C 4-C];
    Y{1} = [0+C 1-C 1-C 0+C];
    colors{1} = [0.5 1 1];

    % PIECE 2
    X{2} = [0+C 0+C 1+C 1+C 2-C 2-C 3-C 3-C];
    Y{2} = [0+C 1-C 1-C 2-C 2-C 1-C 1-C 0+C];
    colors{2} = [1 0.5 1];

    % PIECE 3
    X{3} = [0+C 0+C 1-C 1-C 3-C 3-C];
    Y{3} = [0+C 2-C 2-C 1-C 1-C 0+C];
    colors{3} = [0.5 0.5 1];

    % PIECE 4
    X{4} = [0+C 0+C 2-C 2-C];
    Y{4} = [0+C 2-C 2-C 0+C];
    colors{4} = [1 1 0.5];

    % PIECE 5
    X{5} = [0+C 0+C 2+C 2+C 3-C 3-C];
    Y{5} = [0+C 1-C 1-C 2-C 2-C 0+C];
    colors{5} = [1 0.8 0.5];

    % PIECE 6
    X{6} = [0+C 0+C 1+C 1+C 3-C 3-C 2-C 2-C];
    Y{6} = [0+C 1-C 1-C 2-C 2-C 1+C 1+C 0+C];
    colors{6} = [0.5 1 0.5];

    % PIECE 7
    X{7} = [0+C 0+C 2-C 2-C 3-C 3-C 1+C 1+C];
    Y{7} = [1+C 2-C 2-C 1-C 1-C 0+C 0+C 1+C];
    colors{7} = [1 0.5 0.5];
end

function [] = draw_piece_aux(piece_number, x_displacement, y_displacement, rotations, X, Y, colors, border_width)
    rotations = mod(rotations, 4);
    switch rotations
        case 0
            Xp = X{piece_number};
            Yp = Y{piece_number};
        case 1
            Xp = -Y{piece_number};
            Yp = X{piece_number};
        case 2
            Xp = -X{piece_number};
            Yp = -Y{piece_number};
        case 3
            Xp = Y{piece_number};
            Yp = -X{piece_number};
    end
    patch(Xp + x_displacement, Yp + y_displacement, colors{piece_number}, "LineWidth", border_width, "EdgeColor", colors{piece_number}*0.7);
end

function [] = draw_pieces(pieces, draw_piece)
    for i = 1:size(pieces, 1)
        draw_piece(pieces(i,:))
    end
end