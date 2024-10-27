alpha = 25;
N_extra = 20000; % used for area2 and area3
mesh_res = 0.05; % used for the z interpolation
main(alpha, N_extra, mesh_res)

function main(alpha, N_extra, mesh_res)
    data = load("ex_1_data.mat");
    L = data.L;
    N = data.N;
    x = data.vec_x;
    y = data.vec_y;
    z = data.function_value;

    [xq, yq, zq] = do_plots(L, x, y, z, mesh_res);

    [ area1, alpha_contour ] = get_area1(xq, yq, zq, alpha);
    fprintf("area1 =\n\t"); disp(area1);

    area2 = get_area2(x, y, z, alpha, L, N_extra);
    fprintf("area2 =\n\t"); disp(area2);

    area3 = get_area3(alpha_contour, L, N_extra);
    fprintf("area3 =\n\t"); disp(area3);

    area4 = get_area4(zq, alpha, mesh_res);
    fprintf("area4 =\n\t"); disp(area4);

    area5 = get_area5(zq, alpha, mesh_res);
    fprintf("area5 =\n\t"); disp(area5);
end

function [xq, yq, zq] = do_plots(L, x, y, z, mesh_res)
    figure, stem3(x, y, z), xlabel("x"), ylabel("y"), zlabel("f(x,y)"), title("Points");

    [xq, yq] = meshgrid(0:mesh_res:L, 0:mesh_res:L);
    zq = griddata(x, y, z, xq, yq);
    figure, mesh(xq, yq, zq), xlabel("x"), ylabel("y"), zlabel("f(x,y)"), title("Mesh");
    
    figure, contour(xq, yq, zq), xlabel("x"), ylabel("y"), title("Contours");
end

function [ area, alpha_contour ] = get_area1(x, y, z, alpha)
    figure, alpha_contour = contour(x, y, z, [alpha, alpha]);
    alpha_contour = alpha_contour(:, 2:end);
    area = polyarea(alpha_contour(1, :), alpha_contour(2, :));
end

function [ area ] = get_area2(x, y, z, alpha, L, N)
    extra_points = rand(N, 2) .* L;
    interpolated_z = griddata(x, y, z, extra_points(:, 1), extra_points(:, 2));
    larger_bool = interpolated_z > alpha;
    ratio = sum(larger_bool) / N;
    area =  ratio * L * L;
end

function [ area ] = get_area3(alpha_contour, L, N)
    extra_points = rand(N, 2) .* L;
    in_polygon = inpolygon( ...
        extra_points(:, 1), ...
        extra_points(:, 2), ...
        alpha_contour(1, :), ...
        alpha_contour(2, :) ...
    );
    ratio = sum(in_polygon) / N;
    area =  ratio * L * L;
end

function [ area ] = get_area4(z, alpha, mesh_res)
    bw = z > alpha;
    area = bwarea(bw) * mesh_res * mesh_res;
end

function [ area ] = get_area5(z, alpha, mesh_res)
    bw = z > alpha;
    bw_boundaries = bwboundaries(bw); bw_boundary = bw_boundaries{1};
    area = polyarea(bw_boundary(:, 1), bw_boundary(:, 2)) * mesh_res * mesh_res;
end



